#include "BaseInterface.h"

namespace QCD {
    BaseInterface::BaseInterface()  : QObject() {

    }

    void BaseInterface::run() {

    }

    void BaseInterface::setGuiManager(GuiManager *a_guiManager) {
        m_guiManager = a_guiManager;
    }

} // QCD