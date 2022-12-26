/**
 * @brief constants for QConfigurableDashboard
 */

#ifndef ROBOT_GUI_V3_QCD_H
#define ROBOT_GUI_V3_QCD_H

#include "boost/optional.hpp"

#include "../lib/NlohmannJson/json.hpp"
#include "QMenuBar"
#include "QMenu"
#include "functional"
#include "opencv2/opencv.hpp"

#define QCD_CALLBACK(ptr, func) std::bind(&boost::remove_reference_t<decltype(*ptr)>::func, ptr, std::placeholders::_1)
#define QCD_ID_CALLBACK(ptr, func) std::bind(&boost::remove_reference_t<decltype(*ptr)>::func, ptr, std::placeholders::_1, std::placeholders::_2)

namespace QCD {
    typedef nlohmann::json Json;
    typedef cv::Mat Image;
    typedef std::function<void(Json)> Callback;
    typedef std::function<void(Json, std::string)> IdCallback;

    const char *const THEME_PROPERTY = "theme";
    const char *const WIDGET_BACKGROUND_CLASS = "widgetBackground";
    const char *const CONTAINER_BACKGROUND_CLASS = "containerBackground";
    const char *const HIGHLIGHT_COLOR_CLASS = "highlightColor";
    const char *const TITLE_TEXT_COLOR_CLASS = "titleTextColor";
    const char *const TEXT_COLOR_CLASS = "textColor";
    const char *const BORDER_COLOR_CLASS = "borderColor";

    const char *const TICK_TIME_KEY = "tickTime";
    const char *const TICK_RATE_KEY = "tickRate";
    const char *const TICK_DESIRED_RATE_KEY = "tickDesRate";

    const char *const VIDEO_RECORD_KEY = "recordVideoEvent";
    const char *const VIDEO_RECORD_PATH_KEY = "path";
    const char *const VIDEO_RECORD_ID_KEY = "key";
    const char *const VIDEO_RECORD_TYPE_KEY = "type";

    const int NULL_WIDGET_ID = -1;
    const int CENTRAL_WIDGET_ID = 0;

    enum WidgetFocus {
        NO_FOCUS,
        IN_FOCUS,
        ON_IN_FOCUS,
        ON_NO_FOCUS,
    };
}


#endif //ROBOT_GUI_V3_QCD_H
