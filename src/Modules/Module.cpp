#include <Module.h>
#include <QConfigurableDashboard.h>


namespace QCD {
    AppManager *Module::m_appManager = nullptr;

    Module::Module() : QObject() {
        if(m_appManager == nullptr) {
            throw std::runtime_error("Construct instance of QCD::ConfigurableDashboard before QCD::Module");
        }
    }

    void Module::setAppManager(AppManager *a_appManager) {
        m_appManager = a_appManager;
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