#ifndef QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H
#define QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H

#include "ThreadedModule.h"

namespace QCD {

    class TRandomDataModule : public ThreadedModule {
    Q_OBJECT
    public:
        explicit TRandomDataModule(double a_rate);
    private:
        void tick() override;
        double m_x = 0;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H
