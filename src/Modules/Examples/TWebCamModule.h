#ifndef QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
#define QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H

#include "../ThreadedModule.h"
#include "../../Util/VideoRecorder.h"

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
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
