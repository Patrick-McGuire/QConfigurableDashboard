#include "../include/QConfigurableDashboard.h"
#include "../include/PanelContainer.h"
#include "../include/ButtonWidget.h"
#include "../include/LineDisplayWidget.h"
#include "../include/QCD.h"
#include "iostream"
#include "../include/UtilFunctions.h"
#include "../include/RandomDataModule.h"
#include "../include/TRandomDataModule.h"
#include "../include/WebCamModule.h"
#include "../include/GridContainer.h"
#include "../include/VBoxContainer.h"
#include "../include/HBoxContainer.h"
#include "../include/TabContainer.h"
#include "../include/TextListWidget.h"
#include "../include/GraphWidget.h"
#include "../include/VideoDisplayWidget.h"
#include "../include/VideoRecorderWidget.h"
#include "../include/UtilFunctions.h"
#include "../include/TWebCamModule.h"
#include "../include/TabModule.h"
#include "functional"
#include "../include/VideoRecorder.h"
#include "opencv2/opencv.hpp"
#include "MainPageExample.h"

int main(int argc, char **argv) {
    QCD::QConfigurableDashboard dashboard(argc, argv, 60);

    QCD::TRandomDataModule randomDataInterface(200);
    dashboard.addModule(&randomDataInterface);
    QCD::TWebCamModule webCamStreamInterface(70);
    dashboard.addModule(&webCamStreamInterface);

    QCD::MainPageExample tabModule;
    dashboard.addModule(&tabModule);

    return dashboard.run();
}