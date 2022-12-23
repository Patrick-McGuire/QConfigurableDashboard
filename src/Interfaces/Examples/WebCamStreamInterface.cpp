#include <QLabel>
#include "WebCamStreamInterface.h"
#include "opencv2/opencv.hpp"

namespace QCD {
    WebCamStreamInterface::WebCamStreamInterface(double a_rate) : BaseTimerInterface(a_rate) {
        m_camera = new cv::VideoCapture(0);
    }

    void WebCamStreamInterface::onUpdate() {
        if(m_camera->isOpened()) {
            Image frame;
            Image frame2;
            *m_camera >> frame;
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            frame.copyTo(frame2);
            cv::rectangle(frame2, cv::Rect(10, 10, 100, 100), cv::Scalar(0, 0, 255), 2);
            m_dataPasser->getImageMap()["CAM1"] = frame;
            m_dataPasser->getImageMap()["CAM2"] = frame2;
        }
    }

} // QCD