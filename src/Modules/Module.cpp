#include "Module.h"
#include "../QConfigurableDashboard.h"

namespace QCD {
    Module::Module() : QObject() {
        m_appManager = nullptr;
        m_app = nullptr;
    }

    void Module::setAppManager(AppManager *a_guiManager) {
        m_appManager = a_guiManager;
    }

    AppManager *Module::getAppManager() {
        return m_appManager;
    }

    void Module::setApp(QConfigurableDashboard *a_app) {
        m_app = a_app;
    }

    QConfigurableDashboard *Module::getApp() {
        return m_app;
    }

    void Module::run() {

    }

    void Module::update() {

    }

    void Module::finish() {

    }


} // QCD