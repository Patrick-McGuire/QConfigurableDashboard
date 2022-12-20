#include "src/QConfigurableDashboard.h"
#include "src/Widgets/WidgetContainers/PanelContainer.h"
#include "src/Widgets/CustomWidgets/ButtonWidget.h"
#include "src/Widgets/CustomWidgets/LineDisplayWidget.h"
#include "src/QCD.h"
#include "iostream"
#include "src/Util/UtilFuntions.h"
#include "src/Interfaces/Examples/RandomDataInterface.h"
#include "src/Widgets/WidgetContainers/GridContainer.h"
#include "src/Widgets/WidgetContainers/VBoxContainer.h"
#include "src/Widgets/WidgetContainers/HBoxContainer.h"
#include "src/Widgets/WidgetContainers/TabContainer.h"


int main(int argc, char **argv) {
    QCD::QConfigurableDashboard dashboard(argc, argv);

    dashboard.addMenu("Test");
    dashboard.addMenu("Test2");
    dashboard.addMenu("Thing1", "Settings");
    dashboard.addMenu("Bing","Thing1");
    dashboard.addMenuAction("Bong","Thing1");
    dashboard.addMenu("Thing2", "Settings");
    dashboard.addMenuAction("Yo", "File");

    QCD::RandomDataInterface randomDataInterface(10);
    dashboard.addInterface(&randomDataInterface);

    auto *panelCollection = new QCD::PanelContainer();
    dashboard.setCentralWidget(panelCollection);

    auto *button = new QCD::ButtonWidget("Hi yall");
    auto *button2 = new QCD::ButtonWidget("Sup bro");
    auto *button3 = new QCD::ButtonWidget("agkjbbkjasd");
    auto *button4 = new QCD::ButtonWidget("industral");
    auto *label1 = new QCD::LineDisplayWidget();
    panelCollection->addWidget(button, 50, 50);
    panelCollection->addWidget(button3, 50, 100);
    panelCollection->addWidget(button4, 100, 50);
    panelCollection->addWidget(label1, 200, 200);

    panelCollection->setBackgroundWidget(button2, Qt::AlignHCenter);

    auto *grid = new QCD::TabContainer();
    auto *label2 = new QCD::LineDisplayWidget();
    auto *label3 = new QCD::LineDisplayWidget();
    auto *label4 = new QCD::PanelContainer();
    auto *label5 = new QCD::ButtonWidget("Test12");
    grid->addTab(label2, "T1");
    grid->addTab(label3, "T2");
    grid->addTab(label4, "T3");
    grid->addTab(label5, "T4");
    panelCollection->setBackgroundWidget(grid);

    return dashboard.run();
}
