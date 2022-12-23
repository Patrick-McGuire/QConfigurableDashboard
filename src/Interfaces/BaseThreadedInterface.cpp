#include "BaseThreadedInterface.h"

namespace QCD {
    BaseThreadedInterface::BaseThreadedInterface() {
        m_thread = nullptr;
        m_autoClear = false;
        m_active = false;
    }

    void BaseThreadedInterface::run() {
        m_active = true;
        m_thread = new std::thread(&BaseThreadedInterface::onRun, this);
    }


    void BaseThreadedInterface::setJson(const std::string &a_key, Json &a_value) {
        LockGard gard(m_mutex);
        m_jsonData[a_key] = a_value;
    }

    void BaseThreadedInterface::setImage(const std::string &a_key, const Image &a_image) {
        m_images[a_key] = a_image;
    }

    void BaseThreadedInterface::onRun() {}

    void BaseThreadedInterface::update() {
        // This function should only be called from the main thread, but needs to access memory shared with m_thread
        LockGard gard(m_mutex);
        if (std::this_thread::get_id() != m_thread->get_id()) {
            // Iterate though all updated json values, and copy them into the main thread's DataPasser
            auto &data = m_dataPasser->getInputData();
            for (const auto &el: m_jsonData.items()) {
                data[el.key()] = el.value();
            }
            // Iterate though all updated images
            auto &imgData = m_dataPasser->getImageMap();
            for (const auto &el: m_images) {
                imgData[el.first] = el.second;
            }
        }
        // Remove all json values. This improves performance for code with update rates slower than the main update rate
        // Turn on in constructor of derived with: m_autoClear = true;
        if (m_autoClear) {
            m_jsonData.clear();
        }
    }

    void BaseThreadedInterface::finish() {
        // Tell the thread to finish
        {
            LockGard gard(m_mutex);
            m_active = false;
        }
        // Wait for this thread to finish
        m_thread->join();
    }

} // QCD