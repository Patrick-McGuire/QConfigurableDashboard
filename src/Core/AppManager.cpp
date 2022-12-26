#include <iostream>
#include <AppManager.h>
#include <QCD.h>
#include <opencv2/opencv.hpp>


namespace QCD {

    AppManager::AppManager(QConfigurableDashboard *a_app) {
        m_app = a_app;
        m_themeData = Json::parse(R"delim({
            "Dark" : {
                "widgetBackground" : "background-color: rgb(23, 23, 23)",
                "containerBackground" : "background-color: rgb(13,17,23)",
                "highlightColor" : "background-color: rgb(40,40,40)",
                "titleTextColor" : "color: rgb(88,166,255)",
                "textColor" : "color: rgb(139,148,158)",
                "borderColor" : "border : 1px solid white"
            },
            "Light" : {
                "widgetBackground" : "background-color: rgb(250, 250, 250)",
                "containerBackground" : "background-color: rgb(235,235,235)",
                "highlightColor" : "background-color: rgb(200,200,200)",
                "titleTextColor" : "color: rgb(150,0,0)",
                "textColor" : "color: rgb(0,0,0)",
                "borderColor" : "border : 1px solid black"
            },
            "Green" : {
                "widgetBackground" : "background-color: rgb(25, 25, 25)",
                "containerBackground" : "background-color: rgb(20,20,20)",
                "highlightColor" : "background-color: rgb(50,50,50)",
                "titleTextColor" : "color: rgb(10,200,10)",
                "textColor" : "color: rgb(150,150,150)",
                "borderColor" : "border : 1px solid white"
            },
            "Red" : {
                "widgetBackground" : "background-color: rgb(45,0,0)",
                "containerBackground" : "background-color: rgb(30,0,0)",
                "highlightColor" : "background-color: rgb(50,50,50)",
                "titleTextColor" : "color: rgb(0,200,0)",
                "textColor" : "color: rgb(255,0,0)",
                "borderColor" : "border : 1px solid white"
            }
        })delim");
    }

    void AppManager::enableDragging() {
        m_draggingEnabled = true;
    }

    void AppManager::disableDragging() {
        m_draggingEnabled = false;
    }

    Json &AppManager::getInputData() {
        return m_inputData;
    }

    Json &AppManager::getOutputData() {
        return m_outputData;
    }

    Json &AppManager::getConfigData() {
        return m_configData;
    }

    bool AppManager::getDraggingEnabled() const {
        return m_draggingEnabled;
    }

    Json &AppManager::getThemeData() {
        return m_themeData;
    }

    std::map<std::string, Image> &AppManager::getImageMap() {
        return m_images;
    }

    std::string &AppManager::getTheme() {
        return m_theme;
    }

    void AppManager::setTheme(const std::string &a_theme) {
        m_theme = a_theme;
    }

    QConfigurableDashboard *AppManager::getApp() {
        return m_app;
    }


}