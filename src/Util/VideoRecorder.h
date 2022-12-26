#ifndef QCONFIGURABLEDASHBOARD_VIDEORECORDER_H
#define QCONFIGURABLEDASHBOARD_VIDEORECORDER_H

#include "opencv2/opencv.hpp"
#include "../Core/QCD.h"
namespace QCD {

    class VideoRecorder {
    public:
        explicit VideoRecorder(int a_fps, const std::string &a_key);

        void toggleRecording(const Json &a_data);

        void recordFrame(const Image& a_image);

//        void stopRecording(const Json &a_ignore);

        bool recording() const;

    private:
        int m_fps;
        bool m_recording = false;
        int m_videoID = 0;
        int m_width = 0;
        int m_height = 0;
        double m_startTime = 0;
        int m_recordedFrames = 0;
        std::string m_path;
        std::string m_key;
        cv::VideoWriter m_writer;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VIDEORECORDER_H
