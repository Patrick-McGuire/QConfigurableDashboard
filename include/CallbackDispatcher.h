#ifndef QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H
#define QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H

#include <map>
#include <vector>
#include "QCD.h"

namespace QCD {

    class CallbackDispatcher {
    public:
        CallbackDispatcher();

        int registerCallback(const std::string &a_name, const Callback &a_callback);

        int registerIdCallback(const IdCallback &a_callback);

        void triggerCallback(const std::string &a_name, const Json &a_json = Json::object(), int a_excludeIdIndex = -1);

    private:
        std::map<std::string, std::vector<Callback>> m_callbacks;
        std::vector<IdCallback> m_idCallbacks;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H
