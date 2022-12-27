#ifndef QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H
#define QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H

#include <map>
#include <vector>
#include <QCD.h>

namespace QCD {
    /**
     * @class CallbackDispatcher
     * @brief CallbackDispatcher provides a module to register and trigger callbacks based on string identifiers.
     * @details Callbacks are standard functions, and must have 1 argument of type QCD::Json.
     * Alternatively ID Callbacks can be used, which are called regardless of the identifier triggered.
     * ID Callbacks are instead passed 2 arguments (must be of types QCD::Json, std::string). The string will be the identifier.
     * This is primarily used by QCD::ThreadedModule to tunnel events into it's thread.
     * This class is intended to be used as a parent class, and is derived by QCD::AppManager and QCD::ThreadedModule.
     * @see QCD::AppManager
     * @see QCD::ThreadedModule
     * @authors Patrick-McGuire
     */
    class CallbackDispatcher {
    public:
        /**
         * @brief Constructor
         */
        CallbackDispatcher();

        /**
         * @brief Registers a callback to a specified identifier.
         * @details This callback will be triggered when ever some object calls QCD::CallbackDispatcher::triggerCallback() with the same identifier.
         * @param a_identifier String identifier to listen too
         * @param a_callback Callback to call when identifier is triggered
         * @return index of callback in list of callbacks (not really useful yet)
         */
        int registerCallback(const std::string &a_identifier, const Callback &a_callback);

        /**
         * @brief Registers a ID callback.
         * @details This callback will be triggered when ever some object calls QCD::CallbackDispatcher::triggerCallback() regardless of the identifier used.
         * @param a_callback Callback to call when identifier is triggered
         * @return index of callback in list of callbacks. This can be used to prevent recursion/thread locking by passing it as the excludeIdIndex in QCD::CallbackDispatcher::triggerCallback()
         */
        int registerIdCallback(const IdCallback &a_callback);

        /**
         * @brief Triggers all callbacks registered to the specified identifier.
         * @details All callbacks registered with QCD::CallbackDispatcher::registerCallback(), with the same identifier, will be called and passed the specified Json data.
         * This also triggers all ID Callbacks.
         * @param a_identifier String identifier to trigger
         * @param a_json Json data to pass
         * @param a_excludeIdIndex Index in vector of callbacks to skip
         */
        void triggerCallback(const std::string &a_identifier, const Json &a_json = Json::object(), int a_excludeIdIndex = -1);

    private:
        std::map<std::string, std::vector<Callback>> m_callbacks;
        std::vector<IdCallback> m_idCallbacks;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_CALLBACKDISPATCHER_H
