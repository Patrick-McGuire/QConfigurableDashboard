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

        Json &getThemeData();

        void enableDragging();

        void disableDragging();

        bool getDraggingEnabled() const;

    private:
        bool m_draggingEnabled = true;

        Json m_inputData = Json::object();
        Json m_outputData = Json::object();
        Json m_configData = Json::object();
        Json m_themeData = Json::object();
    };
}


#endif //QCONFIGURABLEDASHBOARD_GUIMANAGER_H
