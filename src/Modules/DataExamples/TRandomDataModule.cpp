#include <chrono>
#include <UtilFunctions.h>
#include <TRandomDataModule.h>
#include <QCD.h>


namespace QCD {
    TRandomDataModule::TRandomDataModule(double a_rate) : ThreadedModule(a_rate) {
    }

    void TRandomDataModule::tick() {
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
    }
} // QCD