#include <QLabel>
#include "WebCamStreamInterface.h"
#include "opencv2/opencv.hpp"

namespace QCD {
    WebCamStreamInterface::WebCamStreamInterface(double a_rate) : BaseTimerInterface(a_rate) {
        m_camera = new cv::VideoCapture(0);
    }

    void WebCamStreamInterface::onUpdate() {
        if(m_camera->isOpened()) {
            std::shared_ptr<cv::Mat> img1(new cv::Mat);
            *m_camera >> *img1;
            cv::cvtColor(*img1, *img1, cv::COLOR_BGR2RGB);
            std::shared_ptr<cv::Mat> img2(new cv::Mat);
            img1->copyTo(*img2);
            cv::rectangle(*img2, cv::Rect(10, 10, 100, 100), cv::Scalar(0, 0, 255), 2);
            m_dataPasser->getImageMap()["CAM1"] = img1;
            m_dataPasser->getImageMap()["CAM2"] = img2;
        }
    }

} // QCD