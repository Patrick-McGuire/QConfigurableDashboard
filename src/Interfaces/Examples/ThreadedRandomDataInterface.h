#ifndef QCONFIGURABLEDASHBOARD_THREADEDRANDOMDATAINTERFACE_H
#define QCONFIGURABLEDASHBOARD_THREADEDRANDOMDATAINTERFACE_H

#include "../BaseThreadedInterface.h"

namespace QCD {

    class ThreadedRandomDataInterface : public BaseThreadedInterface {
    Q_OBJECT
    public:
        explicit ThreadedRandomDataInterface(double a_rate);
    private:
        void onRun() override;
        double m_x = 0;
        int m_interval;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_THREADEDRANDOMDATAINTERFACE_H
