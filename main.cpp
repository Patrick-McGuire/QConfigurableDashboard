#include "src/QConfigurableDashboard.h"
#include "src/Widgets/WidgetContainers/PanelContainer.h"
#include "src/Widgets/CustomWidgets/ButtonWidget.h"
//#include "src/Widgets/CustomWidgets/TextListWidget.h"
#include "src/Widgets/CustomWidgets/LineDisplayWidget.h"
#include "src/QCD.h"
#include "iostream"
#include "src/Util/UtilFuntions.h"
#include "src/Interfaces/Examples/RandomDataInterface.h"
#include "src/Interfaces/Examples/ThreadedRandomDataInterface.h"
#include "src/Interfaces/Examples/WebCamStreamInterface.h"
#include "src/Widgets/WidgetContainers/GridContainer.h"
#include "src/Widgets/WidgetContainers/VBoxContainer.h"
#include "src/Widgets/WidgetContainers/HBoxContainer.h"
#include "src/Widgets/WidgetContainers/TabContainer.h"
#include "src/Widgets/CustomWidgets/TextListWidget.h"
#include "src/Widgets/CustomWidgets/GraphWidget.h"
#include "src/Widgets/CustomWidgets/VideoDisplayWidget.h"
#include "QCamera"
#include "opencv2/opencv.hpp"

int main(int argc, char **argv) {

    QCD::QConfigurableDashboard dashboard(argc, argv);
    // Menus
    dashboard.addMenu("Test");
    dashboard.addMenu("Thing1", "Settings");
    dashboard.addMenu("Bing","Thing1");
    dashboard.addMenuAction("Bong","Thing1");
    dashboard.addMenu("Thing2", "Settings");
    dashboard.addMenuAction("Yo", "Settings");
    // Interfaces
    QCD::ThreadedRandomDataInterface randomDataInterface(30);
    dashboard.addInterface(&randomDataInterface);
    QCD::WebCamStreamInterface webCamStreamInterface(60);
    dashboard.addInterface(&webCamStreamInterface);

    // GUI Widgets
    auto *panelCollection = new QCD::PanelContainer();
    dashboard.setCentralWidget(panelCollection);

    auto *tab = new QCD::TabContainer();
    auto *label2 = new QCD::VideoDisplayWidget("CAM2");
    auto *label3 = new QCD::LineDisplayWidget();
    auto *label4 = new QCD::PanelContainer();
    auto *label22 = new QCD::LineDisplayWidget();
    auto *but1 = new QCD::ButtonWidget("Button");
    auto *label32 = new QCD::TextListWidget("Here is a title");

    auto *gphGrid = new QCD::GridContainer();
    auto *graph1 = new QCD::GraphWidget("Graph1");
    auto *graph2 = new QCD::GraphWidget("Graph2");
    auto *graph3 = new QCD::GraphWidget("Graph3");
    auto *graph4 = new QCD::GraphWidget("Graph4");
    auto *graph5 = new QCD::GraphWidget("Graph5");
    auto *graph6 = new QCD::GraphWidget("Graph6");
    gphGrid->addWidget(graph1,0,0);
    gphGrid->addWidget(graph2,1,0);
    gphGrid->addWidget(graph3,2,0);
    gphGrid->addWidget(graph4,0,1);
    gphGrid->addWidget(graph5,1,1);
    gphGrid->addWidget(graph6,2,1);
    graph1->listen("KEY8", "SIN", "Light green");
    graph1->listen("KEY7", "COS", "red");
    graph2->listen("KEY8", "SIN", "Light green");
    graph2->listen("KEY7", "COS", "red");
    graph3->listen("KEY8", "SIN", "Light green");
    graph3->listen("KEY7", "COS", "red");
    graph4->listen("KEY8", "SIN", "Light green");
    graph4->listen("KEY7", "COS", "red");
    graph5->listen("KEY8", "SIN", "Light green");
    graph5->listen("KEY7", "COS", "red");
    graph6->listen("KEY8", "SIN", "Light green");
    graph6->listen("KEY7", "COS", "red");

    label32->listen("KEY1", ":KEY1");
    label32->listen("KEY4", ":KEY4");
    label32->listen("KEY5", ":KEY5");
//    label32->setUpdateRateScale(10);
    label4->addWidget(label22, 100, 100);
    label4->addWidget(label32, 100, 300);
//    label4->addWidget(gp, 100, 200);
    label4->addWidget(but1, 100, 700);

    auto *label5 = new QCD::ButtonWidget("Test12");
    tab->addWidget(label2);
    tab->addWidget(gphGrid, "Graph");
    tab->addWidget(label3);
    tab->addWidget(label4);
    tab->addWidget(label5);
    panelCollection->setBackgroundWidget(tab);

    return dashboard.run();
}
