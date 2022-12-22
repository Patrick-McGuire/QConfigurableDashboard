#ifndef QCONFIGURABLEDASHBOARD_BASETIMERINTERFACE_H
#define QCONFIGURABLEDASHBOARD_BASETIMERINTERFACE_H

#include "BaseInterface.h"
#include "QTimer"

namespace QCD {

    class BaseTimerInterface : public BaseInterface {
    Q_OBJECT
    public:
        explicit BaseTimerInterface(double a_rate);

        void run() override;

    protected slots:
        virtual void onUpdate();

    protected:
        int m_interval;
        QTimer *m_timer;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASETIMERINTERFACE_H
