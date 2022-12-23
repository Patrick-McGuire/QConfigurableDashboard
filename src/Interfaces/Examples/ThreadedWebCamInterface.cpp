#include "ThreadedWebCamInterface.h"

namespace QCD {
    ThreadedWebCamInterface::ThreadedWebCamInterface(double a_rate) {
        m_interval = (int) ((1.0 / a_rate) * 1000);
        m_camera = new cv::VideoCapture(0);
    }

    void ThreadedWebCamInterface::onRun() {
        while (m_active) {
            if(m_camera->isOpened()) {
                Image frame;
                Image frame2;
                *m_camera >> frame;
                cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
                frame.copyTo(frame2);
                cv::rectangle(frame2, cv::Rect(10, 10, 100, 100), cv::Scalar(0, 0, 255), 2);
                setImage("CAM1", frame);
                setImage("CAM2", frame2);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
        }
    }
} // QCD