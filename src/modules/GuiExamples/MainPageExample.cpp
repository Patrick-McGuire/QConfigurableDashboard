#include "MainPageExample.h"
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
#include "../include/QConfigurableDashboard.h"

namespace QCD {
    MainPageExample::MainPageExample() : TabModule() {
        auto *gridContainer1 = new QCD::GridContainer();
        m_tabs->addWidget(gridContainer1, "Primary");
        auto *topLayout = new QCD::HBoxContainer();
        auto *sideLayout = new QCD::VBoxContainer();
        auto *video1 = new QCD::VideoDisplayWidget("CAM2");
        auto *recorder = new QCD::VideoRecorderWidget();
        gridContainer1->addWidget(topLayout, 0, 0);
        gridContainer1->addWidget(recorder, 0, 1);
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
        graph1->listen(QCD::TICK_RATE_KEY, "Real", "red");
        graph1->listen(QCD::TICK_DESIRED_RATE_KEY, "Desired", "Light green");
        sideLayout->addWidget(dataLabel);
        sideLayout->addWidget(graph1);
        graph1->setMinimumSize(700, 400);
        sideLayout->addWidget(new QCD::ButtonWidget("edfg"));
        sideLayout->addWidget(new QCD::ButtonWidget("abcd"));
        topLayout->addWidget(new QCD::ButtonWidget("1"));
        topLayout->addWidget(new QCD::ButtonWidget("2"));
        topLayout->addWidget(new QCD::ButtonWidget("3", "b1"));

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
        panel->addWidget(new QCD::VideoRecorderWidget());
        m_tabs->addWidget(panel, "Panel demo");
        // Create tab 3
        auto *gphGrid = new QCD::GridContainer();
        auto *graph7 = new QCD::GraphWidget("Graph7");
        auto *graph2 = new QCD::GraphWidget("Graph2");
        auto *graph3 = new QCD::GraphWidget("Graph3");
        auto *graph4 = new QCD::GraphWidget("Graph4");
        auto *graph5 = new QCD::GraphWidget("Graph5");
        auto *graph6 = new QCD::GraphWidget("Graph6");
        gphGrid->addWidget(graph7, 0, 0);
        gphGrid->addWidget(graph2, 1, 0);
        gphGrid->addWidget(graph3, 2, 0);
        gphGrid->addWidget(graph4, 0, 1);
        gphGrid->addWidget(graph5, 1, 1);
        gphGrid->addWidget(graph6, 2, 1);
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
        m_tabs->addWidget(gphGrid, "Graphs");
        // Create tab 4
        auto *graph8 = new QCD::GraphWidget("Graph8");
        graph8->listen("KEY1", "::1", "yellow");
        graph8->listen("KEY2", "::2", "red");
        graph8->listen("KEY3", "::3", "light green");
        graph8->listen("KEY4", "::4", "blue");
        m_tabs->addWidget(graph8, "Single widget");
        m_graphs.push_back(graph1);
        m_graphs.push_back(graph2);
        m_graphs.push_back(graph3);
        m_graphs.push_back(graph4);
        m_graphs.push_back(graph5);
        m_graphs.push_back(graph6);
        m_graphs.push_back(graph7);
        m_graphs.push_back(graph8);
        m_app->addMenuAction("Reset graphs", "Settings");
        registerCallback(std::string(MENU_BASE_CALLBACK) + "Reset graphs", QCD_CALLBACK(this, resetGraph));
    }

    void MainPageExample::resetGraph(const Json &a_args) {
        if(a_args.is_string() && a_args.get<std::string>() == std::string(MENU_BASE_CALLBACK) + "Reset graphs") {
            for (auto &el: m_graphs) {
                el->reset();
            }
        }
    }
} // QCD