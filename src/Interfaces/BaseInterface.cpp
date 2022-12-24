#include "BaseInterface.h"

namespace QCD {
    BaseInterface::BaseInterface()  : QObject() {
        m_appManager = nullptr;
    }

    void BaseInterface::run() {

    }

    void BaseInterface::setGuiManager(AppManager *a_guiManager) {
        m_appManager = a_guiManager;
    }

    void BaseInterface::update() {

    }

    void BaseInterface::finish() {

    }

} // QCD