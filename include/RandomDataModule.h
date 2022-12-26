#ifndef QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H
#define QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H

#include "TimerModule.h"

namespace QCD {

    class RandomDataModule : public TimerModule {
        Q_OBJECT
    public:
        explicit RandomDataModule(double a_rate);
    private:
        void onUpdate() override;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H
