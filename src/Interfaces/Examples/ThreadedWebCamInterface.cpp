#include "ThreadedWebCamInterface.h"
#include "../../Util/UtilFuntions.h"

namespace QCD {
    ThreadedWebCamInterface::ThreadedWebCamInterface(double a_rate) : BaseThreadedInterface(a_rate){
        m_camera = new cv::VideoCapture(0);
        m_recorder = new VideoRecorder(24, "CAM2");
    }

    void ThreadedWebCamInterface::tick() {
        if (m_camera->isOpened()) {
            Image frame;
            Image frame2;
            *m_camera >> frame;
            m_recorder->recordFrame(frame.clone());
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            frame.copyTo(frame2);
            cv::rectangle(frame2, cv::Rect(10, 10, 100, 100), cv::Scalar(m_squareColor ? 0 : 255, 0, m_squareColor ? 255 : 0), 2);
            setImage("CAM1", frame);
            setImage("CAM2", frame2);
        }
        if(randomInt(0, 40 * 3) < 3) {
            triggerOutgoingCallback("random1");
        }
    }

    void ThreadedWebCamInterface::setup() {
        registerCallback("b1", QCD_CALLBACK(this, toggleColor));
        registerCallback(VIDEO_RECORD_KEY, QCD_CALLBACK(m_recorder, toggleRecording));
    }

    void ThreadedWebCamInterface::toggleColor(const Json &value) {
        m_squareColor = !m_squareColor;
    }
} // QCD