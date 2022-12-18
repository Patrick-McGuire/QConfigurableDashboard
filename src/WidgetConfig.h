#ifndef QCONFIGURABLEDASHBOARD_WIDGETCONFIG_H
#define QCONFIGURABLEDASHBOARD_WIDGETCONFIG_H

#include "QCD.h"
#include "Util/FlagVariable.h"
#include <cstdint>

namespace QCD {
    enum LocState {
        BACKGROUND,
        FIXED,
        DYNAMIC,
    };
    /**
     * Bit pattern flags to be used with config variables
     */
    enum ConfigFlag : uint16_t {
        NO_FLAG = 0b0,
        VALID = 0b10,
        MAX = 0b100,
        MIN = 0b1000,
        AUTO = 0b10000,
        DEFAULT = 0b100000,
        NONE = 0b1000000,
    };
    /**
     * Config variable definition
     * Using a uint16 because we don't need more than 16 flags
     */
    template<class Var>
    using ConfigVariable = FlagVariable<Var, uint16_t>;


    /**
 * @brief Tracks style of a widget
 */
    typedef struct {
        ConfigVariable<QString> backgroundColor;
        ConfigVariable<QString> borderColor;
        ConfigVariable<QString> textColor;
        ConfigVariable<QString> headerTextColor;
        ConfigVariable<int> fontSize;
    } WidgetStyle;

    /**
     * @brief Tracks configuration of a widget
     */
    typedef struct {
        // Every widget gets a unique ID
        int id;
        // Track dragging status
        LocState locState;
        ConfigVariable<bool> staticPos;
        ConfigVariable<bool> draggable;
        // Track position
        ConfigVariable<int> x;
        ConfigVariable<int> y;

        // Style instance
        WidgetStyle style;

        // Custom data
        void *custom;
    } WidgetConfig;
    const WidgetConfig DEFAULT_WIDGET_CONFIG = {NULL_WIDGET_ID, LocState::DYNAMIC, false, false, 0, 0, {}, nullptr};
}


#endif //QCONFIGURABLEDASHBOARD_WIDGETCONFIG_H
