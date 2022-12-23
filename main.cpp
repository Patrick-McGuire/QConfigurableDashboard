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
    dashboard.addMenu("Bing", "Thing1");
    dashboard.addMenuAction("Bong", "Thing1");
    dashboard.addMenu("Thing2", "Settings");
    dashboard.addMenuAction("Yo", "Settings");
    // Interfaces
    QCD::ThreadedRandomDataInterface randomDataInterface(30);
    dashboard.addInterface(&randomDataInterface);
    QCD::WebCamStreamInterface webCamStreamInterface(60);
    dashboard.addInterface(&webCamStreamInterface);
    // Create the GUI
    auto *tabContainer = new QCD::TabContainer();
    dashboard.setCentralWidget(tabContainer);
    // Create tab 1
    auto *gridContainer1 = new QCD::GridContainer();
    tabContainer->addWidget(gridContainer1, "Primary");
    auto *topLayout = new QCD::HBoxContainer();
    auto *sideLayout = new QCD::VBoxContainer();
    auto *video1 = new QCD::VideoDisplayWidget("CAM2");
    gridContainer1->addWidget(topLayout, 0, 0);
    gridContainer1->addWidget(sideLayout, 1, 1);
    gridContainer1->addWidget(video1, 1, 0);
    topLayout->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    gridContainer1->getLayout()->setAlignment(topLayout, Qt::AlignHCenter);
    sideLayout->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    video1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    auto *dataLabel = new QCD::TextListWidget("Data");
    dataLabel->listen("KEY1", "::1");
    dataLabel->listen("KEY2", "::2");
    dataLabel->listen("KEY3", "::3");
    dataLabel->listen("KEY4", "::4");
    dataLabel->listen("KEY5", "::5");
    dataLabel->listen("KEY6", "::6");
    dataLabel->listen("KEY7", "::7");
    dataLabel->listen("KEY8", "::8");
    auto graph1 = new QCD::GraphWidget("Test graph", "Pickles");
    graph1->listen("KEY8", "SIN", "Light green");
    graph1->listen("KEY7", "COS", "red");
    sideLayout->addWidget(dataLabel);
    sideLayout->addWidget(graph1);
    graph1->setMinimumSize(700, 400);
    sideLayout->addWidget(new QCD::ButtonWidget("defg"));
    sideLayout->addWidget(new QCD::ButtonWidget("abcd"));
    topLayout->addWidget(new QCD::ButtonWidget("dd"));
    topLayout->addWidget(new QCD::ButtonWidget("1"));
    topLayout->addWidget(new QCD::ButtonWidget("2"));
    topLayout->addWidget(new QCD::ButtonWidget("3"));
    // Create tab 2
    auto *panel = new QCD::PanelContainer();
    auto *dataLabel2 = new QCD::TextListWidget("Data2");
    dataLabel2->listen("KEY1", "::1");
    dataLabel2->listen("KEY2", "::2");
    dataLabel2->listen("KEY3", "::3");
    dataLabel2->listen("KEY4", "::4");
    dataLabel2->listen("KEY5", "::5");
    dataLabel2->listen("KEY6", "::6");
    dataLabel2->listen("KEY7", "::7");
    dataLabel2->listen("KEY8", "::8");
    panel->addWidget(dataLabel2, 100, 100);
    panel->addWidget(new QCD::ButtonWidget("3"), 100, 500);
    panel->addWidget(new QCD::ButtonWidget("3"), 300, 100);
    panel->addWidget(new QCD::LineDisplayWidget(), 300, 500);
    tabContainer->addWidget(panel, "Panel demo");
    // Create tab 3
    auto *gphGrid = new QCD::GridContainer();
    auto *graph7 = new QCD::GraphWidget("Graph7");
    auto *graph2 = new QCD::GraphWidget("Graph2");
    auto *graph3 = new QCD::GraphWidget("Graph3");
    auto *graph4 = new QCD::GraphWidget("Graph4");
    auto *graph5 = new QCD::GraphWidget("Graph5");
    auto *graph6 = new QCD::GraphWidget("Graph6");
    gphGrid->addWidget(graph7,0,0);
    gphGrid->addWidget(graph2,1,0);
    gphGrid->addWidget(graph3,2,0);
    gphGrid->addWidget(graph4,0,1);
    gphGrid->addWidget(graph5,1,1);
    gphGrid->addWidget(graph6,2,1);
    graph7->listen("KEY8", "SIN", "Light green");
    graph7->listen("KEY7", "COS", "red");
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
    tabContainer->addWidget(gphGrid, "Graphs");
    // Create tab 4
    auto *graph8 = new QCD::GraphWidget("Graph8");
    graph8->listen("KEY1", "::1", "yellow");
    graph8->listen("KEY2", "::2", "red");
    graph8->listen("KEY3", "::3", "light green");
    graph8->listen("KEY4", "::4", "blue");
    tabContainer->addWidget(graph8, "Single widget");

    return dashboard.run();
}
