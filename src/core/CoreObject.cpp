#include "CoreObject.h"

namespace QCD {
    const char *THEME_HARDCODED_STYLE = R"delim({
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
        })delim";


    // Protected
//    bool CoreObject::m_staticInit = false;
    bool CoreObject::m_draggingEnabled = false;
    Json CoreObject::m_inputData;
    Json CoreObject::m_outputData;
    Json CoreObject::m_configData;
    Json CoreObject::m_themeData;
    ImageMap CoreObject::m_images;
    std::string CoreObject::m_theme;
    QConfigurableDashboard *CoreObject::m_app;
    // Private
    CallbackDispatcher *CoreObject::m_callbackDispatcher = nullptr;

    CoreObject::CoreObject() = default;

    CoreObject::CoreObject(QConfigurableDashboard *a_app) {
        if(a_app != m_app) {
            delete m_callbackDispatcher;
            m_app = a_app;
            m_inputData = Json::object();
            m_outputData = Json::object();
            m_configData = Json::object();
            m_themeData = Json::parse(THEME_HARDCODED_STYLE);
            m_callbackDispatcher = new CallbackDispatcher();
        }
    }

    int CoreObject::run() {
        return 0;
    }

    void CoreObject::runUpdate(bool a_focus) {}

    void CoreObject::finish() {}

    void CoreObject::registerCallback(const std::string &a_identifier, const Callback &a_callback) {
        m_callbackDispatcher->registerCallback(a_identifier, a_callback);                                           // Pointer can't be null here
    }

    int CoreObject::registerTunnelCallback(const TunnelCallback &a_callback) {
        return m_callbackDispatcher->registerTunnelCallback(a_callback);
    }

    void CoreObject::triggerCallback(const std::string &a_identifier, const Json &a_json, int a_excludeIdIndex) {
        m_callbackDispatcher->triggerCallback(a_identifier, a_json, a_excludeIdIndex);
    }

    void CoreObject::setTheme(const std::string &a_theme) {
        m_theme = a_theme;
    }

    std::string &CoreObject::getTheme() {
        return m_theme;
    }

} // QCD