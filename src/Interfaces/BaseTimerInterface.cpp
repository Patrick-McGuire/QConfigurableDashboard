#include "BaseTimerInterface.h"

namespace QCD {
    BaseTimerInterface::BaseTimerInterface(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);
        m_timer = new QTimer();
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    }

    void BaseTimerInterface::run() {
        m_timer->start(m_interval);
    }

    void BaseTimerInterface::onUpdate() {}
} // QCD