#include "GuiManager.h"

namespace QCD {

    GuiManager::GuiManager() {

    }

    void GuiManager::enableDragging() {
        m_draggingEnabled = true;
    }

    void GuiManager::disableDragging() {
        m_draggingEnabled = false;
    }

    Json &GuiManager::getInputData() {
        return m_inputData;
    }

    Json &GuiManager::getOutputData() {
        return m_outputData;
    }

    Json &GuiManager::getConfigData() {
        return m_configData;
    }

    bool GuiManager::getDraggingEnabled() const {
        return m_draggingEnabled;
    }

}