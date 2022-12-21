#ifndef QCONFIGURABLEDASHBOARD_DATAPASSER_H
#define QCONFIGURABLEDASHBOARD_DATAPASSER_H

#include "QCD.h"
#include "../lib/NlohmannJson/json.hpp"
#include "map"
#include "memory"
#include "opencv2/opencv.hpp"

namespace QCD {
    class DataPasser {
    public:
        DataPasser();

        Json &getInputData();

        Json &getOutputData();

        Json &getConfigData();

        Json &getThemeData();

        std::map<std::string, std::shared_ptr<cv::Mat>> &getImageMap();

        void enableDragging();

        void disableDragging();

        bool getDraggingEnabled() const;

    private:
        bool m_draggingEnabled = false;

        Json m_inputData = Json::object();
        Json m_outputData = Json::object();
        Json m_configData = Json::object();
        Json m_themeData = Json::object();
        std::map<std::string, std::shared_ptr<cv::Mat>> m_images;
    };
}


#endif //QCONFIGURABLEDASHBOARD_DATAPASSER_H
