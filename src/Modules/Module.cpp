#include <Module.h>
#include <QConfigurableDashboard.h>


namespace QCD {
    Module::Module() : QObject() {
        m_appManager = nullptr;
    }

    void Module::setAppManager(AppManager *a_guiManager) {
        m_appManager = a_guiManager;
    }

    AppManager *Module::getAppManager() {
        return m_appManager;
    }

    void Module::run() {

    }

    void Module::update() {

    }

    void Module::finish() {

    }


} // QCD