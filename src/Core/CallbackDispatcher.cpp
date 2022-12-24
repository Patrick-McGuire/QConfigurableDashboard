#include "CallbackDispatcher.h"

namespace QCD {
    CallbackDispatcher::CallbackDispatcher() = default;

    void CallbackDispatcher::registerCallback(const std::string &a_name, const Callback &a_callback) {
        m_callbacks[a_name].push_back(a_callback);
    }

    void CallbackDispatcher::registerIdCallback(const IdCallback &a_callback) {
        m_idCallbacks.push_back(a_callback);
    }

    void CallbackDispatcher::triggerCallback(const std::string &a_name, const Json &a_json) {
        if(a_name.empty()) return;
        // Trigger callbacks by name
        if (m_callbacks.count(a_name) != 0) {
            auto &callbacks = m_callbacks[a_name];
            for (auto &func: callbacks) {
                func(a_json);
            }
        }
        // Trigger all id callbacks
        for (auto &func: m_idCallbacks) {
            func(a_json, a_name);
        }

    }
} // QCD