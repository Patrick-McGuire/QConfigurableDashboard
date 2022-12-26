#include <CallbackDispatcher.h>

namespace QCD {
    CallbackDispatcher::CallbackDispatcher() = default;

    int CallbackDispatcher::registerCallback(const std::string &a_name, const Callback &a_callback) {
        m_callbacks[a_name].push_back(a_callback);
        return (int) m_callbacks[a_name].size() - 1;
    }

    int CallbackDispatcher::registerIdCallback(const IdCallback &a_callback) {
        m_idCallbacks.push_back(a_callback);
        return (int) m_idCallbacks.size() - 1;
    }

    void CallbackDispatcher::triggerCallback(const std::string &a_name, const Json &a_json, int a_excludeIdIndex) {
        if (a_name.empty()) return;
        // Trigger callbacks by name
        if (m_callbacks.count(a_name) != 0) {
            auto &callbacks = m_callbacks[a_name];
            for (auto &func: callbacks) {
                func(a_json);
            }
        }
        // Trigger all id callbacks
        for (int i = 0; i < m_idCallbacks.size(); i++) {
            if (i != a_excludeIdIndex) {
                m_idCallbacks[i](a_json, a_name);
            }
        }

    }
} // QCD