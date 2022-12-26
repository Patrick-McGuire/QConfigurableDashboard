#include <QLabel>
#include "WebCamModule.h"
#include "opencv2/opencv.hpp"

namespace QCD {
    WebCamModule::WebCamModule(double a_rate) : TimerModule(a_rate) {
        m_camera = new cv::VideoCapture(0);
    }

    void WebCamModule::onUpdate() {
        if(m_camera->isOpened()) {
            Image frame;
            Image frame2;
            *m_camera >> frame;
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            frame.copyTo(frame2);
            cv::rectangle(frame2, cv::Rect(10, 10, 100, 100), cv::Scalar(0, 0, 255), 2);
            m_appManager->getImageMap()["CAM1"] = frame;
            m_appManager->getImageMap()["CAM2"] = frame2;
        }
    }

} // QCD