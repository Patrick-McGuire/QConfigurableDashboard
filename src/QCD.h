/**
 * @brief constants for QConfigurableDashboard
 */

#ifndef ROBOT_GUI_V3_QCD_H
#define ROBOT_GUI_V3_QCD_H

#include "boost/optional.hpp"
#include "QString"
#include "../lib/NlohmannJson/json.hpp"

namespace QCD {
    typedef nlohmann::json Json;


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
