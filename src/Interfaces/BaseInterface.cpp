#include "BaseInterface.h"

namespace QCD {
    BaseInterface::BaseInterface()  : QObject() {

    }

    void BaseInterface::run() {

    }

    void BaseInterface::setGuiManager(DataPasser *a_guiManager) {
        m_guiManager = a_guiManager;
    }

} // QCD