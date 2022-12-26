#ifndef QCONFIGURABLEDASHBOARD_VIDEODISPLAYWIDGET_H
#define QCONFIGURABLEDASHBOARD_VIDEODISPLAYWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "Widget.h"

namespace QCD {

    class VideoDisplayWidget : public Widget {
    Q_OBJECT
    public:
        explicit VideoDisplayWidget(const std::string &a_key = "");

        void listen(const std::string &a_key);

        void setSize(int a_width, int a_height);

        static const int AUTO_SIZE = -1;

    private:
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QVBoxLayout *m_layout;
        QLabel *m_videoWidget;
        std::string m_key;
        int m_width = AUTO_SIZE, m_height = AUTO_SIZE;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VIDEODISPLAYWIDGET_H
