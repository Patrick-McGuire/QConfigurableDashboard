
#ifndef QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H
#define QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include "../BaseWidget.h"

namespace QCD {

    class LineDisplayWidget : public BaseWidget {
        Q_OBJECT
    public:
        LineDisplayWidget();

    protected:
        void onUpdate(QCD::WidgetFocus a_focus) override;

    private:
        QVBoxLayout *m_layout;
        QLabel *m_textBox;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H
