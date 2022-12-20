#include <iostream>
#include "GuiManager.h"

namespace QCD {

    GuiManager::GuiManager() {
        m_themeData = Json::parse(R"delim({
            "Dark" : {
                "widgetBackground" : "background-color: rgb(23, 23, 23)",
                "containerBackground" : "background-color: rgb(13,17,23)",
                "highlightColor" : "background-color: rgb(40,40,40)",
                "titleTextColor" : "color: rgb(88,166,255)",
                "textColor" : "color: rgb(139,148,158)"
            },
            "Light" : {
                "widgetBackground" : "background-color: rgb(250, 250, 250)",
                "containerBackground" : "background-color: rgb(235,235,235)",
                "highlightColor" : "background-color: rgb(200,200,200)",
                "titleTextColor" : "color: rgb(150,0,0)",
                "textColor" : "color: rgb(0,0,0)"
            },
            "Green" : {
                "widgetBackground" : "background-color: rgb(25, 25, 25)",
                "containerBackground" : "background-color: rgb(20,20,20)",
                "highlightColor" : "background-color: rgb(50,50,50)",
                "titleTextColor" : "color: rgb(10,200,10)",
                "textColor" : "color: rgb(150,150,150)"
            },
            "Red" : {
                "widgetBackground" : "background-color: rgb(45,0,0)",
                "containerBackground" : "background-color: rgb(30,0,0)",
                "highlightColor" : "background-color: rgb(50,50,50)",
                "titleTextColor" : "color: rgb(0,200,0)",
                "textColor" : "color: rgb(255,0,0)"
            }
        })delim");
    }

    void GuiManager::enableDragging() {
        m_draggingEnabled = true;
    }

    void GuiManager::disableDragging() {
        m_draggingEnabled = false;
    }

    Json &GuiManager::getInputData() {
        return m_inputData;
    }

    Json &GuiManager::getOutputData() {
        return m_outputData;
    }

    Json &GuiManager::getConfigData() {
        return m_configData;
    }

    bool GuiManager::getDraggingEnabled() const {
        return m_draggingEnabled;
    }

    Json &GuiManager::getThemeData() {
        return m_themeData;
    }

}