#ifndef QCONFIGURABLEDASHBOARD_COREOBJECT_H
#define QCONFIGURABLEDASHBOARD_COREOBJECT_H

#include <QCD.h>
#include <CallbackDispatcherInterface.h>
#include <CallbackDispatcher.h>

namespace QCD {
    class QConfigurableDashboard;       // Forward decl

    /**
     * @brief core object extended by all QCD classes
     * @details Provides a callback and data interface to all QCD classes.
     * @see QCD::CallbackDispatcher
     */
    class CoreObject : public CallbackDispatcherInterface {
    public:
        /**
         * @brief Constructor
         */
        CoreObject();

        /**
         * @brief Constructor
         * @details This constructor should only be called once per application, inside QCD::QConfigurableDashboard
         * @param a_app QConfigurableDashboard object
         */
        explicit CoreObject(QConfigurableDashboard *a_app);

        virtual int run();

        virtual void runUpdate(bool a_focus);

        virtual void finish();

        /**
         * @brief Registers a callback to a specified identifier.
         * @details This callback will be triggered when ever some object calls QCD::CallbackDispatcher::triggerCallback() with the same identifier.
         * @param a_identifier String identifier to listen too
         * @param a_callback Callback to call when identifier is triggered
         */
        void registerCallback(const std::string &a_identifier, const Callback &a_callback) override;

        /**
         * @brief Registers a tunnel callback.
         * @details This callback will be triggered when ever some object calls QCD::CallbackDispatcher::triggerCallback() regardless of the identifier used.
         * @param a_callback Callback to call when identifier is triggered
         * @return index of callback in list of callbacks. This can be used to prevent recursion/thread locking by passing it as the excludeIdIndex in QCD::CallbackDispatcher::triggerCallback()
         */
        int registerTunnelCallback(const TunnelCallback &a_callback) override;

        /**
         * @brief Triggers all callbacks registered to the specified identifier.
         * @details All callbacks registered with QCD::CallbackDispatcher::registerCallback(), with the same identifier, will be called and passed the specified Json data.
         * This also triggers all tunnel Callbacks.
         * @param a_identifier String identifier to trigger
         * @param a_json Json data to pass
         * @param a_excludeIdIndex Index in vector of callbacks to skip
         */
        void triggerCallback(const std::string &a_identifier, const Json &a_json = Json::object(), int a_excludeIdIndex = -1) override;

        /**
         * @brief Sets the current theme
         * @param a_theme Name of theme to set
         */
        static void setTheme(const std::string &a_theme);

        /**
         * @brief Gets the name of the current theme
         * @return name
         */
        std::string &getTheme();

    protected:
        static bool m_draggingEnabled;                  ///< If the application allows dragging of widgets currently (only applicable to widgets in panel containers)
        static Json m_inputData;                        ///< Data sent from modules and read by widgets
        static Json m_outputData;                       ///< Data sent from widgets to modules
        static Json m_configData;                       ///< App wide config info
        static Json m_themeData;                        ///< Theme stuff (redoing?)
        static ImageMap m_images;                       ///< Images sent from modules to widgets
        static QConfigurableDashboard *m_app;           ///< Pointer to app for everyone to access

    private:
        static std::string m_theme;                             // Track current theme
        static CallbackDispatcher *m_callbackDispatcher;        // This is private so that we can wrap its methods making the interface a little cleaner
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_COREOBJECT_H
