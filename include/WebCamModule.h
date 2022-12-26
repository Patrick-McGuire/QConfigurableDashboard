#ifndef QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H
#define QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H

#include "TimerModule.h"
#include "opencv2/opencv.hpp"
#include "QLabel"

namespace QCD {

    class WebCamModule : public TimerModule {
        Q_OBJECT
    public:
        explicit WebCamModule(double a_rate);

    private:
        void onUpdate() override;

        cv::VideoCapture *m_camera;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H
