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

    bool GuiManager::getDragState() const {
        return m_draggingEnabled;
    }

    Json &GuiManager::getInputData() {
        return inputData;
    }

    Json &GuiManager::getOutputData() {
        return outputData;
    }

    Json &GuiManager::getConfigData() {
        return configData;
    }

    bool GuiManager::getDraggingEnabled() const {
        return m_draggingEnabled;
    }

}