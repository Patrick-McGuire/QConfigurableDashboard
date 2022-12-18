#include "src/QConfigurableDashboard.h"
#include "src/Widgets/WidgetContainers/PanelCollection.h"
#include "src/Widgets/CustomWidgets/ButtonWidget.h"
#include "src/Widgets/CustomWidgets/LineDisplayWidget.h"
#include "src/QCD.h"
#include "iostream"

#include "lib/NlohmannJson/json.hpp"

using namespace nlohmann;

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void do1() {
    json json1 = json::object();
    json1["AKEY1"] = "adfs";
    json1["AKEY2"] = "adfs";
    json1["AKEY3"] = "adfs";
    json1["AKEY4"] = "adfs";
    json1["AKEY5"] = "adfs";
    json1["AKEY6"] = "adfs";
    json1["AKEY7"] = "adfs";
    json1["KEY1"] = "adfs";
    json1["KEY2"] = "adfs";
    json1["KEY3"] = "adfs";
    json1["KEY4"] = "adfs";
    json1["KEY5"] = "adfs";
    json1["KEY6"] = "adfs";
    json1["KEY7"] = "adfs";

    for (int i = 0; i < 100000; i++) {
        json &ref = json1["KEY7"];
        if (ref.is_string()) {
            auto &b = ref.get_ref<std::string &>();
        }
    }
}

void do2() {
    json json1 = QCD::Json::object();
    json1["AKEY1"] = "adfs";
    json1["AKEY2"] = "adfs";
    json1["AKEY3"] = "adfs";
    json1["AKEY4"] = "adfs";
    json1["AKEY5"] = "adfs";
    json1["AKEY6"] = "adfs";
    json1["AKEY7"] = "adfs";
    json1["KEY1"] = "adfs";
    json1["KEY2"] = "adfs";
    json1["KEY3"] = "adfs";
    json1["KEY4"] = "adfs";
    json1["KEY5"] = "adfs";
    json1["KEY6"] = "adfs";
    json1["KEY7"] = "adfs";
    for (int i = 0; i < 100000; i++) {
        if (json1.contains("KEY7")) {
            json &ref = json1["KEY7"];
            if (ref.is_string()) {
                auto &b = ref.get_ref<std::string &>();
            }
        }
    }
}

int main(int argc, char **argv) {
//    uint64_t start;
//
//    uint64_t cnt1 = 0;
//    int num1 = 0;
//
//    uint64_t cnt2 = 0;
//    int num2 = 0;
//
//    for (int i = 0; i < 20; i++) {
//        start = timeSinceEpochMillisec();
//        do1();
//        cnt1 += timeSinceEpochMillisec() - start;
//        num1++;
//        std::cout << "1:" << timeSinceEpochMillisec() - start << "\n";
//
//        start = timeSinceEpochMillisec();
//        do2();
//        cnt2 += timeSinceEpochMillisec() - start;
//        num2++;
//        std::cout << "2:" << timeSinceEpochMillisec() - start << "\n";
//
//    }
//
//    std::cout << "\n\n\n\n-------------------------\n";
//    std::cout << "#1:" << cnt1 / num1 << "\n";
//    std::cout << "#2:" << cnt2 / num2 << "\n";
//    int a = 0;
//
//    for (int i = 0; i < 100000; i++) {
//        json json1 = json::object();
//        json1["KEY1"] = json("adfs");
//
//        if (json1.contains("KEY1") && json1["KEY1"].is_string()) {
//            std::string b = json1["KEY1"].get<std::string>();
//        }
////        if (json1.contains("KEY1")) {
////            json &ref = json1["KEY1"];
////            if (ref.is_string()) {
////                auto &b = ref.get_ref<std::string &>();
////            }
////        }
//
//    }
//    std::cout << timeSinceEpochMillisec() - start << ":" << a << "\n";

//    }






    QCD::QConfigurableDashboard dashboard(argc, argv);

    auto *panelCollection = new QCD::PanelCollection();
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
