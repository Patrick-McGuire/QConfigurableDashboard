#include "VideoDisplayWidget.h"

namespace QCD {
    VideoDisplayWidget::VideoDisplayWidget(const std::string &a_key) : BaseWidget() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        setLayout(m_layout);
        m_videoWidget = new QLabel();
        m_layout->addWidget(m_videoWidget);
        m_layout->setAlignment(Qt::AlignCenter);
        m_key = a_key;
        m_videoWidget->setMinimumSize(1, 1);
    }

    void VideoDisplayWidget::listen(const std::string &a_key) {
        m_key = a_key;
    }

    void VideoDisplayWidget::onUpdate(QCD::WidgetFocus a_focus) {
        if (isInFocus(a_focus)) {
            auto map = m_dataPasser->getImageMap();
            if (map.count(m_key) != 0) {
                int w = m_width <= 0 ? size().width() - 5 : m_width;
                int h = m_height <= 0 ? size().height() - 5 : m_height;
                auto rgb_image = map[m_key];
                m_videoWidget->setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)).scaled(w, h,
                                                                                                                                                                    Qt::KeepAspectRatio));
            }
        }
    }

    void VideoDisplayWidget::setSize(int a_width, int a_height) {
        m_width = a_width;
        m_height = a_height;
    }
} // QCD