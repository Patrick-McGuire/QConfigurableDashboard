#include "RandomDataInterface.h"
#include "../../Util/UtilFuntions.h"

namespace QCD {
    RandomDataInterface::RandomDataInterface(double a_rate) : BaseTimerInterface(a_rate) {

    }

    void RandomDataInterface::update() {
        Json &data = m_guiManager->getInputData();
        data["KEY1"] = randomInt(-100, 100);
        data["KEY2"] = randomInt(-10, 10);
        data["KEY3"] = randomDouble(-100, 100);
        data["KEY4"] = randomDouble(0, 1);;
        data["KEY5"] = randomString(10);
        data["KEY6"] = randomString(10);;
    }

} // QCD