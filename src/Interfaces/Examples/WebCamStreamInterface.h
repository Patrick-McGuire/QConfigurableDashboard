#ifndef QCONFIGURABLEDASHBOARD_WEBCAMSTREAMINTERFACE_H
#define QCONFIGURABLEDASHBOARD_WEBCAMSTREAMINTERFACE_H

#include "../BaseTimerInterface.h"
#include "opencv2/opencv.hpp"
#include "QLabel"

namespace QCD {

    class WebCamStreamInterface : public BaseTimerInterface {
        Q_OBJECT
    public:
        explicit WebCamStreamInterface(double a_rate);

    private:
        void update() override;

        cv::VideoCapture *m_camera;
        QLabel label;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_WEBCAMSTREAMINTERFACE_H
