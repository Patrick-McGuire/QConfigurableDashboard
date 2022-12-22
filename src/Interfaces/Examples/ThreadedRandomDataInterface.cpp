#include "ThreadedRandomDataInterface.h"
#include "../../Util/UtilFuntions.h"
#include <chrono>

namespace QCD {
    ThreadedRandomDataInterface::ThreadedRandomDataInterface(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);;
    }

    void ThreadedRandomDataInterface::onRun() {
        std::string s = "Testname";
        while (m_active) {
            pthread_setname_np(pthread_self(), s.c_str());
            Json value = randomInt(-100, 100);
            setJson("KEY1", value);
            value = randomInt(-10, 10);
            setJson("KEY2", value);
            value = randomDouble(-100, 100);
            setJson("KEY3", value);
            value = randomDouble(0, 1);
            setJson("KEY4", value);
            value = randomString(randomInt(5, 15));
            setJson("KEY5", value);
            value = randomString(10);
            setJson("KEY6", value);
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
        }
    }
} // QCD