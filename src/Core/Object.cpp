#include "Object.h"

namespace QCD {
    bool Object::m_staticInit = false;
    bool Object::m_draggingEnabled = false;
    Json Object::m_inputData;
    Json Object::m_outputData;
    Json Object::m_configData;
    Json Object::m_themeData;
    ImageMap Object::m_images;
    std::string Object::m_theme;
    QConfigurableDashboard *Object::m_app;

    Object::Object() {
        if (!m_staticInit) {
            m_staticInit = true;
            m_inputData = Json::object();
            m_outputData = Json::object();
            m_configData = Json::object();
            m_themeData = Json::object();
        }
    }

    void Object::run() {}

    void Object::runUpdate() {}

    void Object::finish() {}
} // QCD