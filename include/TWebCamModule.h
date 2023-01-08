#ifndef QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
#define QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H

#include "ThreadedModule.h"
#include "VideoRecorder.h"

namespace QCD {
    /**
     * @class TWebCamModule
     * @brief Populates the image data structure with the webcam
     * @details Provides two images, under keys CAM1 and CAM2. First is unmodified, second had a box drawn on it
     */
    class TWebCamModule : public ThreadedModule {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate Update rate
         */
        explicit TWebCamModule(double a_rate);

        /**
         * @brief Switches the color of the box drawn
         * @details Connected to internal events for testing
         * @param value
         */
        void toggleColor(const Json &value);

    private:
        /**
         * @brief Populates the images
         * @details Provides two images, under keys CAM1 and CAM2. First is unmodified, second had a box drawn on it
         */
        void tick() override;

        cv::VideoCapture *m_camera;
        bool m_squareColor = false;
        VideoRecorder *m_recorder;
        VideoRecorder *m_recorder2;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TWEBCAMMODULE_H
