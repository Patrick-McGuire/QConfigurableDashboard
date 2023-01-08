#ifndef QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H
#define QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H

#include "TimerModule.h"
#include "opencv2/opencv.hpp"
#include "QLabel"

namespace QCD {
    /**
     * @class WebCamModule
     * @brief Populates the image data structure with the webcam
     * @details Provides two images, under keys CAM1 and CAM2. First is unmodified, second had a box drawn on it
     */
    class WebCamModule : public TimerModule {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate Update rate
         */
        explicit WebCamModule(double a_rate);

    private:
        /**
         * @brief Populates the images
         * @details Provides two images, under keys CAM1 and CAM2. First is unmodified, second had a box drawn on it
         */
        void onUpdate() override;

        cv::VideoCapture *m_camera;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_WEBCAMMODULE_H
