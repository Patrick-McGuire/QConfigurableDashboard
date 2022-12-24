#ifndef QCONFIGURABLEDASHBOARD_DATAPASSER_H
#define QCONFIGURABLEDASHBOARD_DATAPASSER_H

#include "QCD.h"
#include "../lib/NlohmannJson/json.hpp"
#include "map"
#include "memory"
#include "opencv2/opencv.hpp"
#include "QObject"
#include "CallbackDispatcher.h"

namespace QCD {
    class DataPasser : public QObject, public CallbackDispatcher {
    Q_OBJECT
    public:
        DataPasser();

        Json &getInputData();

        Json &getOutputData();

        Json &getConfigData();

        Json &getThemeData();

        std::map<std::string, Image> &getImageMap();

        void enableDragging();

        void disableDragging();

        bool getDraggingEnabled() const;

        void setTheme(const std::string &a_theme);

        std::string &getTheme();

    signals:
        void themeChanged();

    private:
        bool m_draggingEnabled = false;

        Json m_inputData = Json::object();
        Json m_outputData = Json::object();
        Json m_configData = Json::object();
        Json m_themeData = Json::object();
        std::map<std::string, Image> m_images;
        std::string m_theme;
    };
}


#endif //QCONFIGURABLEDASHBOARD_DATAPASSER_H
