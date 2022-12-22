#ifndef QCONFIGURABLEDASHBOARD_RANDOMDATAINTERFACE_H
#define QCONFIGURABLEDASHBOARD_RANDOMDATAINTERFACE_H

#include "../BaseTimerInterface.h"

namespace QCD {

    class RandomDataInterface : public BaseTimerInterface {
        Q_OBJECT
    public:
        explicit RandomDataInterface(double a_rate);
    private:
        void onUpdate() override;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_RANDOMDATAINTERFACE_H
