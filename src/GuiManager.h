#ifndef QCONFIGURABLEDASHBOARD_GUIMANAGER_H
#define QCONFIGURABLEDASHBOARD_GUIMANAGER_H

#include "QCD.h"
#include "../lib/NlohmannJson/json.hpp"

namespace QCD {
    class GuiManager {
    public:
        GuiManager();

        Json &getInputData();
        Json &getOutputData();
        Json &getConfigData();

        void enableDragging();

        void disableDragging();

        bool getDraggingEnabled() const;

    private:
        bool m_draggingEnabled = true;

        Json inputData = Json::object();
        Json outputData = Json::object();
        Json configData = Json::object();

        bool getDragState() const;
    };
}


#endif //QCONFIGURABLEDASHBOARD_GUIMANAGER_H
