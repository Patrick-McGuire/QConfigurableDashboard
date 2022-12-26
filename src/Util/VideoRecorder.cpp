#include <UtilFunctions.h>
#include <VideoRecorder.h>
#include <QCD.h>

namespace QCD {
    VideoRecorder::VideoRecorder(int a_fps, const std::string &a_key) {
        m_fps = a_fps;
        m_path = "video";
        m_key = a_key;

    }

    void VideoRecorder::toggleRecording(const Json &a_data) {
        if (!a_data.is_object()) return;


        bool rec = m_recording;
        std::string key;
        std::string path;
        Json other = a_data;
        const Json &recJ = other[VIDEO_RECORD_TYPE_KEY];
        const Json &keyJ = other[VIDEO_RECORD_ID_KEY];
        const Json &pathJ = other[VIDEO_RECORD_PATH_KEY];
        if (recJ.is_boolean()) rec = recJ.get<bool>();
        else return;
        if (keyJ.is_string()) key = keyJ.get<std::string>();
        else return;
        if (pathJ.is_string()) path = pathJ.get<std::string>();
        else return;

        if (key != m_key) return;
        m_path = path + "/" + key;

        if (!m_recording && rec) {
            qDebug("Recording starting\n");
            m_recording = true;
            m_videoID++;
            std::string path2 = m_path + "_"+ std::to_string(m_videoID) + ".avi";
            m_writer.open(path2, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), m_fps, cv::Size(m_width, m_height));

            m_startTime = getEpochTime();
            m_recordedFrames = 0;
        } else if (m_recording && !rec) {
            qDebug("Recording stopping\n");
            m_recording = false;
            m_writer.release();
        }
    }

    void VideoRecorder::recordFrame(const Image &a_image) {
        m_width = a_image.cols;
        m_height = a_image.rows;

        if (m_recording) {
            double dt = getEpochTime() - m_startTime;
            int desiredFrames = (int) (dt * (double) m_fps);
            if (desiredFrames - m_recordedFrames > 1) {
                qWarning("WARNING: Recorded frame drop: %d", desiredFrames - m_recordedFrames);
            }
            while (m_recordedFrames < desiredFrames) {
                m_writer.write(a_image);
                m_recordedFrames++;
            }
        }
    }

    bool VideoRecorder::recording() const {
        return m_recording;
    }
}