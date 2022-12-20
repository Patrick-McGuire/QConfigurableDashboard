/**
 * @brief constants for QConfigurableDashboard
 */

#ifndef ROBOT_GUI_V3_QCD_H
#define ROBOT_GUI_V3_QCD_H

#include "boost/optional.hpp"
#include "QString"
#include "../lib/NlohmannJson/json.hpp"
#include "QMenuBar"
#include "QMenu"

namespace QCD {
    typedef nlohmann::json Json;

    const char *const THEME_PROPERTY = "theme";
    const char *const WIDGET_BACKGROUND_CLASS = "widgetBackground";
    const char *const CONTAINER_BACKGROUND_CLASS = "containerBackground";
    const char *const HIGHLIGHT_COLOR_CLASS = "highlightColor";
    const char *const TITLE_TEXT_COLOR_CLASS = "titleTextColor";
    const char *const TEXT_COLOR_CLASS = "textColor";


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
