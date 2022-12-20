#ifndef QCONFIGURABLEDASHBOARD_DATAPASSER_H
#define QCONFIGURABLEDASHBOARD_DATAPASSER_H

#include "QCD.h"
#include "../lib/NlohmannJson/json.hpp"

namespace QCD {
    class DataPasser {
    public:
        DataPasser();

        Json &getInputData();

        Json &getOutputData();

        Json &getConfigData();

        Json &getThemeData();

        void enableDragging();

        void disableDragging();

        bool getDraggingEnabled() const;

    private:
        bool m_draggingEnabled = false;

        Json m_inputData = Json::object();
        Json m_outputData = Json::object();
        Json m_configData = Json::object();
        Json m_themeData = Json::object();
    };
}


#endif //QCONFIGURABLEDASHBOARD_DATAPASSER_H
