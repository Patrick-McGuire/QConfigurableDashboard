#include "src/QConfigurableDashboard.h"
#include "src/Widgets/WidgetContainers/PanelContainer.h"
#include "src/Widgets/CustomWidgets/ButtonWidget.h"
#include "src/Widgets/CustomWidgets/LineDisplayWidget.h"
#include "src/QCD.h"
#include "iostream"
#include "src/Util/UtilFuntions.h"
#include "src/Interfaces/Examples/RandomDataInterface.h"


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

    return dashboard.run();
}
