#include <UtilFunctions.h>
#include <RandomDataModule.h>

namespace QCD {
    RandomDataModule::RandomDataModule(double a_rate) : TimerModule(a_rate) {

    }

    void RandomDataModule::onUpdate() {
        m_inputData["KEY1"] = randomInt(-100, 100);
        m_inputData["KEY2"] = randomInt(-10, 10);
        m_inputData["KEY3"] = randomDouble(-100, 100);
        m_inputData["KEY4"] = randomDouble(0, 1);;
        m_inputData["KEY5"] = randomString(randomInt(5, 15));
        m_inputData["KEY6"] = randomString(10);
    }

} // QCD