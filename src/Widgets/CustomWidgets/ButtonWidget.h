
#ifndef QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H
#define QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include "../BaseWidget.h"

namespace QCD {
    class ButtonWidget : public BaseWidget {
    Q_OBJECT
    public:
        ButtonWidget(const QString &text = "");

    private slots:
        void onClick();

        void onRelease();
    private:
        QVBoxLayout *m_layout;
        bool m_state = false;
        QPushButton *m_pushButton;
    };
}


#endif //QCONFIGURABLEDASHBOARD_BUTTONWIDGET_H
