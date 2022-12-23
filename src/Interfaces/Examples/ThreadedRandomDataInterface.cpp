#include "ThreadedRandomDataInterface.h"
#include "../../Util/UtilFuntions.h"
#include <chrono>

namespace QCD {
    ThreadedRandomDataInterface::ThreadedRandomDataInterface(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);
    }

    void ThreadedRandomDataInterface::onRun() {
        while (m_active) {
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
            value = sin(m_x) * 3;
            setJson("KEY7", value);
            value = cos(m_x) * 2;
            m_x += 0.1;
            setJson("KEY8", value);
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
        }
    }
} // QCD