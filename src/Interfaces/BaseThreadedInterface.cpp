#include "BaseThreadedInterface.h"

namespace QCD {
    //// Thread/operational functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BaseThreadedInterface::BaseThreadedInterface(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);
        m_thread = nullptr;
        m_autoClear = false;
        m_active = false;
    }

    void BaseThreadedInterface::run() {
        // Start event tunneling
        m_dataPasser->registerIdCallback(QCD_ID_CALLBACK(this, queueCallback));
        // Start the thread
        m_active = true;
        m_thread = new std::thread(&BaseThreadedInterface::internalRun, this);
    }

    void BaseThreadedInterface::finish() {
        // Tell the thread to finish
        {
            LockGard gard(m_threadMutex);
            m_active = false;
        }
        // Wait for this thread to finish
        m_thread->join();
    }

    void BaseThreadedInterface::internalRun() {
        setup();
        while (m_active) {
            triggerIncomingCallbacks();
            tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
        }
    }

    void BaseThreadedInterface::tick() {}

    void BaseThreadedInterface::setup() {}

    bool BaseThreadedInterface::isThisThread() {
        LockGard gard(m_threadMutex);
        return std::this_thread::get_id() == m_thread->get_id();
    }

    //// Data I/O functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BaseThreadedInterface::setJson(const std::string &a_key, Json &a_value) {
        LockGard gard(m_dataMutex);
        m_outgoingData[a_key] = a_value;
    }

    void BaseThreadedInterface::setImage(const std::string &a_key, const Image &a_image) {
        m_outgoingImages[a_key] = a_image;
    }

    void BaseThreadedInterface::update() {
        // This function should only be called from the main thread, but needs to access memory shared with m_thread
        LockGard gard(m_dataMutex);
        if (!isThisThread()) {
            // Iterate though all updated json values, and copy them into the main thread's DataPasser
            auto &data = m_dataPasser->getInputData();
            for (const auto &el: m_outgoingData.items()) {
                data[el.key()] = el.value();
            }
            // Iterate though all updated images
            auto &imgData = m_dataPasser->getImageMap();
            for (const auto &el: m_outgoingImages) {
                imgData[el.first] = el.second;
            }
            // Copy in the incoming data
            m_incomingData = m_dataPasser->getOutputData();     // Copying so much ugh
            // Trigger all pending callbacks
            while (!m_outgoingEventQueue.empty()) {
                auto &callback = m_outgoingEventQueue.front();
                m_dataPasser->triggerCallback(callback.first, callback.second);
                m_outgoingEventQueue.pop();
            }
            // Remove all json values. This improves performance for code with update rates slower than the main update rate
            // Turn on in constructor of derived with: m_autoClear = true;
            if (m_autoClear) {
                m_outgoingData.clear();
                m_outgoingImages.clear();
            }
        }

    }

    Json &BaseThreadedInterface::getIncomingData() {
        return m_incomingData;
    }

    //// Callback I/O functions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void BaseThreadedInterface::queueCallback(const Json &a_json, const std::string &a_name) {
        LockGard gard(m_eventMutex);                                        // Establish a lock on the event variables
        if (!isThisThread()) {                                                 // This should never run from this thread
            m_incomingEventQueue.push({a_name, a_json});
        }
    }

    void BaseThreadedInterface::triggerIncomingCallbacks() {
        while (!m_incomingEventQueue.empty()) {
            auto &callback = m_incomingEventQueue.front();
            triggerCallback(callback.first, callback.second);
            m_incomingEventQueue.pop();
        }
    }

    void BaseThreadedInterface::triggerOutgoingCallback(const std::string &a_name, const Json &a_json) {
        m_outgoingEventQueue.push({a_name, a_json});
    }


} // QCD