#ifndef QCONFIGURABLEDASHBOARD_TIMERMODULE_H
#define QCONFIGURABLEDASHBOARD_TIMERMODULE_H

#include "Module.h"
#include "QTimer"

namespace QCD {

    class TimerModule : public Module {
    Q_OBJECT
    public:
        explicit TimerModule(double a_rate);

        void run() override;

    protected slots:
        virtual void onUpdate();

    protected:
        int m_interval;
        QTimer *m_timer;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TIMERMODULE_H
