#ifndef QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H
#define QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H

#include "../BaseThreadedInterface.h"

namespace QCD {

    class ThreadedWebCamInterface : public BaseThreadedInterface {
    Q_OBJECT
    public:
        explicit ThreadedWebCamInterface(double a_rate);
    private:

        void onRun() override;

        int m_interval;
        cv::VideoCapture *m_camera;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H
