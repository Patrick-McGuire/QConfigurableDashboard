#include "src/QConfigurableDashboard.h"
#include "src/Widgets/WidgetContainers/PanelContainer.h"
#include "src/Widgets/CustomWidgets/ButtonWidget.h"
//#include "src/Widgets/CustomWidgets/TextListWidget.h"
#include "src/Widgets/CustomWidgets/LineDisplayWidget.h"
#include "src/QCD.h"
#include "iostream"
#include "src/Util/UtilFuntions.h"
#include "src/Interfaces/Examples/RandomDataInterface.h"
#include "src/Widgets/WidgetContainers/GridContainer.h"
#include "src/Widgets/WidgetContainers/VBoxContainer.h"
#include "src/Widgets/WidgetContainers/HBoxContainer.h"
#include "src/Widgets/WidgetContainers/TabContainer.h"
#include "src/Widgets/CustomWidgets/TextListWidget.h"


int main(int argc, char **argv) {
    QCD::QConfigurableDashboard dashboard(argc, argv);

    dashboard.addMenu("Test");
    dashboard.addMenu("Thing1", "Settings");
    dashboard.addMenu("Bing","Thing1");
    dashboard.addMenuAction("Bong","Thing1");
    dashboard.addMenu("Thing2", "Settings");
    dashboard.addMenuAction("Yo", "Settings");

    QCD::RandomDataInterface randomDataInterface(10);
    dashboard.addInterface(&randomDataInterface);

    auto *panelCollection = new QCD::PanelContainer();
    dashboard.setCentralWidget(panelCollection);

    auto *grid = new QCD::TabContainer();
    auto *label2 = new QCD::TextListWidget("Yo what up");
    label2->listen("KEY1", ":KEY1");
    label2->listen("KEY3", ":KEY3");
    label2->listen("KEY5", ":KEY5");
    auto *label3 = new QCD::LineDisplayWidget();

    auto *label4 = new QCD::PanelContainer();
    auto *label22 = new QCD::LineDisplayWidget();
    auto *label32 = new QCD::TextListWidget("Here is a title");
    label32->listen("KEY2", ":KEY2");
    label32->listen("KEY4", ":KEY4");
    label32->listen("KEY6", ":KEY6");
    label4->addWidget(label22, 100, 100);
    label4->addWidget(label32, 100, 300);

    auto *label5 = new QCD::ButtonWidget("Test12");
    grid->addWidget(label2);
    grid->addWidget(label3);
    grid->addWidget(label4);
    grid->addWidget(label5);
    panelCollection->setBackgroundWidget(grid);

    return dashboard.run();
}
