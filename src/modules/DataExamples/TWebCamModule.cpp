#include <UtilFunctions.h>
#include <TWebCamModule.h>
#include <QCD.h>


namespace QCD {
    TWebCamModule::TWebCamModule(double a_rate) : ThreadedModule(a_rate){
        m_camera = new cv::VideoCapture(0);
        m_recorder = new VideoRecorder(24, "CAM1");
        m_recorder2 = new VideoRecorder(24, "CAM2");
    }

    void TWebCamModule::tick() {
        if (m_camera->isOpened()) {
            Image frame;
            Image frame2;
            *m_camera >> frame;
            m_recorder->recordFrame(frame);
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            frame.copyTo(frame2);
            cv::rectangle(frame2, cv::Rect(10, 10, 100, 100), cv::Scalar(m_squareColor ? 0 : 255, 0, m_squareColor ? 255 : 0), 2);
            m_recorder2->recordFrame(frame2);
            setImage("CAM1", frame);
            setImage("CAM2", frame2);
        }
        if(randomInt(0, 40 * 3) < 3) {
            triggerCallback("random1");
        }
    }

    void TWebCamModule::setup() {
        registerCallback("b1", QCD_CALLBACK(this, toggleColor));
        registerCallback(VIDEO_RECORD_CALLBACK, QCD_CALLBACK(m_recorder, toggleRecording));
        registerCallback(VIDEO_RECORD_CALLBACK, QCD_CALLBACK(m_recorder2, toggleRecording));
    }

    void TWebCamModule::toggleColor(const Json &value) {
        m_squareColor = !m_squareColor;
    }
} // QCD