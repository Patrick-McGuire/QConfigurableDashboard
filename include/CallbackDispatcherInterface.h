#ifndef QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHERINTERFACE_H
#define QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHERINTERFACE_H

#include <QCD.h>

namespace QCD {

    /**
     * @brief Interface definition for callback dispatchers
     * @details Pure virtual interface to retain common function names across app
     */
    class CallbackDispatcherInterface {
        virtual void registerCallback(const std::string &a_identifier, const Callback &a_callback) = 0;

        virtual void triggerCallback(const std::string &a_identifier, const Json &a_json = Json::object(), int a_excludeIdIndex = -1) = 0;

        virtual int registerTunnelCallback(const TunnelCallback &a_callback) = 0;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHERINTERFACE_H
