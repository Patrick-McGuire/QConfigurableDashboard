#include <CallbackDispatcher.h>

namespace QCD {
    CallbackDispatcher::CallbackDispatcher() = default;

    void CallbackDispatcher::registerCallback(const std::string &a_identifier, const Callback &a_callback) {
        m_callbacks[a_identifier].push_back(a_callback);
    }

    int CallbackDispatcher::registerTunnelCallback(const TunnelCallback &a_callback) {
        m_tunnelCallbacks.push_back(a_callback);
        return (int) m_tunnelCallbacks.size() - 1;
    }

    void CallbackDispatcher::triggerCallback(const std::string &a_identifier, const Json &a_json, int a_excludeIdIndex) {
        if (a_identifier.empty()) return;
        // Trigger callbacks by name
        if (m_callbacks.count(a_identifier) != 0) {
            auto &callbacks = m_callbacks[a_identifier];
            for (auto &func: callbacks) {
                func(a_json);
            }
        }
        // Trigger all tunnel Callbacks
        for (int i = 0; i < m_tunnelCallbacks.size(); i++) {
            if (i != a_excludeIdIndex) {
                m_tunnelCallbacks[i](a_json, a_identifier);
            }
        }

    }
} // QCD