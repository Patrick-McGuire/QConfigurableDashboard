#include <ThreadedModule.h>

namespace QCD {
    //// Thread/operational functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ThreadedModule::ThreadedModule(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);
        m_thread = nullptr;
        m_autoClear = false;
        m_active = false;
    }

    int ThreadedModule::run() {
        // Start event tunneling
        m_callbackID = registerTunnelCallback(QCD_TUNNEL_CALLBACK(this, queueCallback));
        // Start the thread
        m_active = true;
        m_thread = new std::thread(&ThreadedModule::internalRun, this);
        return 0;
    }

    void ThreadedModule::finish() {
        // Tell the thread to finish
        {
            LockGard gard(m_threadMutex);
            m_active = false;
        }
        // Wait for this thread to finish
        m_thread->join();
    }

    void ThreadedModule::internalRun() {
        setup();
        while (m_active) {
            triggerIncomingCallbacks();
            tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
        }
    }

    void ThreadedModule::tick() {}

    void ThreadedModule::setup() {}

    bool ThreadedModule::isThisThread() {
        LockGard gard(m_threadMutex);
        return std::this_thread::get_id() == m_thread->get_id();
    }

    //// Data I/O functions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void ThreadedModule::setJson(const std::string &a_key, Json &a_value) {
        LockGard gard(m_dataMutex);
        m_outgoingData[a_key] = a_value;
    }

    void ThreadedModule::setImage(const std::string &a_key, const Image &a_image) {
        LockGard gard(m_dataMutex);
        m_outgoingImages[a_key] = a_image;
    }

    void ThreadedModule::runUpdate(bool a_focus) {
        // This function should only be called from the main thread, but needs to access memory shared with m_thread
        if (!isThisThread()) {
            // Handle incoming and outgoing data
            {
                LockGard gard2(m_dataMutex);
                // Iterate though all updated json values, and copy them into the main thread's CallbackDispatcher
                for (const auto &el: m_outgoingData.items()) {
                    m_inputData[el.key()] = el.value();
                }
                // Iterate though all updated images
                for (const auto &el: m_outgoingImages) {
                    m_images[el.first] = el.second;
                }
                // Copy in the incoming data
                m_incomingData = m_outputData;     // Copying so much ugh
                // Remove all json values. This improves performance for code with update rates slower than the main runUpdate rate
                // Turn on in constructor of derived with: m_autoClear = true;
                if (m_autoClear) {
                    m_outgoingData.clear();
                    m_outgoingImages.clear();
                }
            }
            // Handle outgoing events
            {
                LockGard gard(m_eventMutex);
                // Trigger all pending callbacks
                while (!m_outgoingEventQueue.empty()) {
                    auto &callback = m_outgoingEventQueue.front();
                    CoreObject::triggerCallback(callback.first, callback.second, m_callbackID);
                    m_outgoingEventQueue.pop();
                }
            }
        }

    }

    Json &ThreadedModule::getIncomingData() {
        return m_incomingData;
    }

    //// Callback I/O functions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void ThreadedModule::queueCallback(const Json &a_json, const std::string &a_name) {
        if (!isThisThread()) {                                                 // This should never run from this thread
            LockGard gard(m_eventMutex);                                    // Establish a lock on the event variables
            m_incomingEventQueue.push({a_name, a_json});
        }
    }

    void ThreadedModule::triggerIncomingCallbacks() {
        LockGard gard(m_eventMutex);                                        // Establish a lock on the event variables
        while (!m_incomingEventQueue.empty()) {
            auto &callback = m_incomingEventQueue.front();
            m_dispatcher.triggerCallback(callback.first, callback.second);
            m_incomingEventQueue.pop();
        }
    }

    void ThreadedModule::triggerCallback(const std::string &a_name, const Json &a_json, int a_excludeIdIndex) {
        LockGard gard(m_eventMutex);                                        // Establish a lock on the event variables
        m_outgoingEventQueue.push({a_name, a_json});
    }

    void ThreadedModule::registerCallback(const std::string &a_identifier, const Callback &a_callback) {
        m_dispatcher.registerCallback(a_identifier, a_callback);
    }


} // QCD