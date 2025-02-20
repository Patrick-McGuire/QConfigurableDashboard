
#ifndef QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H
#define QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include "Widget.h"

namespace QCD {
    class ButtonWidget : public Widget {
    Q_OBJECT
    public:
        explicit ButtonWidget(const QString &a_text = "", const QString &a_pub = "");

        void publishTo(const std::string &a_key, bool onClick = true);

    signals:
        void pressed();

        void released();

    private slots:
        void onClick();

        void onRelease();
    private:
        QVBoxLayout *m_layout;
        bool m_state = false;
        QPushButton *m_pushButton;
        std::string m_outputKey;
        std::string m_outputKey2;
    };
}


#endif //QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H
