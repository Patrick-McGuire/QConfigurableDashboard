#ifndef QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H
#define QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H

#include "../BaseThreadedInterface.h"
#include "../../Util/VideoRecorder.h"

namespace QCD {

    class ThreadedWebCamInterface : public BaseThreadedInterface {
    Q_OBJECT
    public:
        explicit ThreadedWebCamInterface(double a_rate);

        void toggleColor(const Json &value);

    private:
        void setup() override;

        void tick() override;

        cv::VideoCapture *m_camera;
        bool m_squareColor = false;
        VideoRecorder *m_recorder;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_THREADEDWEBCAMINTERFACE_H
