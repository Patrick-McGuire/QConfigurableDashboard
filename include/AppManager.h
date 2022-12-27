#ifndef QCONFIGURABLEDASHBOARD_APPMANAGER_H
#define QCONFIGURABLEDASHBOARD_APPMANAGER_H

#include <QCD.h>
#include "../lib/NlohmannJson/json.hpp"
#include <map>
#include <memory>
#include <opencv2/opencv.hpp>
#include <QObject>
#include <CallbackDispatcher.h>

namespace QCD {
    class QConfigurableDashboard;       // Forward decl

    /**
     * @class AppManager
     * @brief Handles coordination and data tunneling across application
     * @details Essentially every QCD object will have a pointer to a common instance of this object. This is how data is transferred between modules and widgets.
     * This also provides a callback system for events.
     * There are a handful of types of data that can be transferred with this object:
     * @par
     * - @b Json @b input
     *  - Json object for passing data from modules to widgets
     * - @b Json @b output
     *  - Json object for passing data from widget to modules
     * - @b Json @b config
     *  - Application wide config data (unsupported currently)
     * - @b Json @b theme
     *  - Theme data (changing at some point)
     * - @b Image @b input
     *  - Key-value map of Images for passing from widgets to modules
     *  @see The way callback events are handled is defined int QCD::CallbackDispatcher
     *  @authors Patrick-McGuire
     */
    class AppManager : public QObject, public CallbackDispatcher {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_app QConfigurableDashboard application
         * @note This is constructed internally once, and should never be called outside of QCD::QConfigurableDashboard.
         */
        explicit AppManager(QConfigurableDashboard *a_app);

        /**
         * @brief Gets a reference to the input json object
         * @return Json reference
         */
        Json &getInputData();

        /**
         * @brief Gets a reference to the output json object
         * @return Json reference
         */
        Json &getOutputData();

        /**
         * Gets a reference to the config json object
         * @return Json reference
         */
        Json &getConfigData();

        /**
         * Gets a reference to the theme json object
         * @return Json reference
         */
        Json &getThemeData();

        /**
         * Gets a reference to the map of images
         * @return Map reference
         */
        ImageMap &getImageMap();

        /**
         * @brief Enable dragging across Application
         * @details Enables dragging for all widgets capable of being dragged
         */
        void enableDragging();

        /**
         * @brief Disables dragging across Application
         * @details Disables dragging for all widgets capable of being dragged
         */
        void disableDragging();

        /**
         * @brief Gets if dragging is enabled across the Application
         * @details Gets if dragging is enabled for all widgets capable of being dragged
         * @return if enabled
         */
        bool getDraggingEnabled() const;

        /**
         * @brief Sets the name of the current theme
         * @note This is handled internally, and should never be called outside of QCD's core classes.
         * @param a_name String name
         */
        void setTheme(const std::string &a_name);

        /**
         * @brief Gets the name of the current theme
         * @return Name of current theme
         */
        std::string &getTheme();

        /**
         * Gets a pointer to the QConfigurableDashboard object for the application
         * @return QConfigurableDashboard pointer
         */
        QConfigurableDashboard *getApp();

    signals:

        /**
         * @brief Re-doing with callbacks soon
         */
        void themeChanged();

    private:
        bool m_draggingEnabled = false;

        Json m_inputData = Json::object();
        Json m_outputData = Json::object();
        Json m_configData = Json::object();
        Json m_themeData = Json::object();
        ImageMap m_images;
        std::string m_theme;

        QConfigurableDashboard *m_app;
    };
}


#endif //QCONFIGURABLEDASHBOARD_APPMANAGER_H
