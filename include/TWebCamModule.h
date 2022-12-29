#ifndef QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
#define QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H

#include "ThreadedModule.h"
#include "VideoRecorder.h"

namespace QCD {

    class TWebCamModule : public ThreadedModule {
    Q_OBJECT
    public:
        explicit TWebCamModule(double a_rate);

        void toggleColor(const Json &value);

    private:
        void setup() override;

        void tick() override;

        cv::VideoCapture *m_camera;
        bool m_squareColor = false;
        VideoRecorder *m_recorder;
        VideoRecorder *m_recorder2;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
