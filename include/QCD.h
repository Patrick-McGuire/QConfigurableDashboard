/**
 * @file QCD.h
 * @brief Constants for QConfigurableDashboard
 */

#ifndef ROBOT_GUI_V3_QCD_H
#define ROBOT_GUI_V3_QCD_H

#include "../lib/NlohmannJson/json.hpp"
#include "QMenuBar"
#include "QMenu"
#include "functional"
#include "opencv2/opencv.hpp"
#include <map>

/**
 * @brief Create callback for use with QCD's custom event structure
 * @details This creates a standard function with 1 argument (must be of type QCD::Json) from a pointer and a method.
 * This can be used with QCD::CallbackDispatcher::registerCallback()
 * @see QCD::AppManager
 * @see QCD::ThreadedModule
 * @see QCD::CallbackDispatcher
 * @param ptr pointer to object to call function on
 * @param func function call
 * @pre func is a member of ptr
 * @pre func takes 1 argument of type QCD::Json
 */
#define QCD_CALLBACK(ptr, func) std::bind(&std::remove_pointer<decltype(ptr)>::type::func, ptr, std::placeholders::_1)
/**
 * @brief Create callback for use with QCD's custom event structure
 * @details This creates a standard function with 2 arguments (must be of types QCD::Json, std::string) from a pointer and a method.
 * This can be used with QCD::CallbackDispatcher::registerIdCallback()
 * @see QCD::AppManager
 * @see QCD::ThreadedModule
 * @see QCD::CallbackDispatcher
 * @param ptr pointer to object to call function on
 * @param func function call
 * @pre func is a member of ptr
 * @pre func takes 2 arguments of types QCD::Json, std::string
 */
#define QCD_ID_CALLBACK(ptr, func) std::bind(&std::remove_pointer<decltype(ptr)>::type::func, ptr, std::placeholders::_1, std::placeholders::_2)

/**
 * @namespace QCD
 * @brief Namespace encompassing QConfigurableDashboard
 * @authors Patrick-McGuire
 */
namespace QCD {
    // TODO: link to proper library's
    typedef nlohmann::json Json;                                                    ///< Json format used throughout QConfigurableDashboard, from nlohmann json
    typedef cv::Mat Image;                                                          ///< Image format used throughout QConfigurableDashboard, from opencv
    typedef std::map<std::string, Image> ImageMap;                                  ///< Image map format used throughout QConfigurableDashboard
    typedef std::function<void(Json)> Callback;                                     ///< Callback format used for our implementation of events
    typedef std::function<void(Json, std::string)> IdCallback;                      ///< Callback format used underlying our implementation of events

    const char *const THEME_PROPERTY = "theme";                                     ///< Name of QWidget property used for themes
    const char *const WIDGET_BACKGROUND_CLASS = "widgetBackground";                 ///< CSS class equivalent identifier for widget background color
    const char *const CONTAINER_BACKGROUND_CLASS = "containerBackground";           ///< CSS class equivalent identifier for widget container background color
    const char *const HIGHLIGHT_COLOR_CLASS = "highlightColor";                     ///< CSS class equivalent identifier for widget highlight/hover color
    const char *const TITLE_TEXT_COLOR_CLASS = "titleTextColor";                    ///< CSS class equivalent identifier for widget title text color
    const char *const TEXT_COLOR_CLASS = "textColor";                               ///< CSS class equivalent identifier for widget normal text color
    const char *const BORDER_COLOR_CLASS = "borderColor";                           ///< CSS class equivalent identifier for widget border color

    const char *const TICK_TIME_KEY = "tickTime";                                   ///< Reserved input data key updated with the loop time of the application
    const char *const TICK_RATE_KEY = "tickRate";                                   ///< Reserved input data key updated with the update rate of the application
    const char *const TICK_DESIRED_RATE_KEY = "tickDesRate";                        ///< Reserved input data key updated with the desired update rate of the application

    const char *const VIDEO_RECORD_KEY = "recordVideoEvent";                        ///< Reserved callback identifier for starting/stopping recording of video
    const char *const VIDEO_RECORD_PATH_KEY = "path";                               ///< Json key for video recording: path
    const char *const VIDEO_RECORD_ID_KEY = "key";                                  ///< Json key for video recording: image map key
    const char *const VIDEO_RECORD_TYPE_KEY = "type";                               ///< Json key for video recording: start/stop specifier

    /**
     * @enum WidgetFocus
     * @brief States to track a widgets current visibility
     * @details This enum is passed to the QCD::Widget::onUpdate() function to
     * provide information about the current visibility of a widget
     * @note Use QCD::Widget::isInFocus(WidgetFocus) to check if a widget is visible
     */
    enum WidgetFocus {
        NO_FOCUS,        ///< Widget is not currently visible (except on first update when coming out of focus, then value is ON_NO_FOCUS)
        IN_FOCUS,        ///< Widget is visible (except on first update when coming into focus, then value is ON_IN_FOCUS)
        ON_IN_FOCUS,     ///< First update when Widget is coming into focus
        ON_NO_FOCUS,     ///< First update when Widget is coming out of focus
    };
}


#endif //ROBOT_GUI_V3_QCD_H
