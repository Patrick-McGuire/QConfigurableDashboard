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
        void onUpdate() override;

        cv::VideoCapture *m_camera;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_WEBCAMSTREAMINTERFACE_H
