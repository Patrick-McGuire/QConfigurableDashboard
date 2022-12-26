
#ifndef QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H
#define QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include "../Widget.h"

namespace QCD {

    class LineDisplayWidget : public Widget {
        Q_OBJECT
    public:
        explicit LineDisplayWidget(const std::string &a_key = "KEY5");

        void listen(const std::string &a_key);

    protected:
        void onUpdate(QCD::WidgetFocus a_focus) override;

    private:
        QVBoxLayout *m_layout;
        QLabel *m_textBox;
        std::string m_key;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_LINEDISPLAYWIDGET_H
