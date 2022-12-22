#include "BaseInterface.h"

namespace QCD {
    BaseInterface::BaseInterface()  : QObject() {
        m_dataPasser = nullptr;
    }

    void BaseInterface::run() {

    }

    void BaseInterface::setGuiManager(DataPasser *a_guiManager) {
        m_dataPasser = a_guiManager;
    }

    void BaseInterface::update() {

    }

    void BaseInterface::finish() {

    }

} // QCD