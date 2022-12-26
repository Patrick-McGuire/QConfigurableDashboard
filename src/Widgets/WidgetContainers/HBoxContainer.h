#ifndef QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H

#include "Container.h"
#include "QHBoxLayout"

namespace QCD {

    class HBoxContainer : public Container {
    Q_OBJECT
    public:
        explicit HBoxContainer();

        bool addWidget(Widget *a_baseWidget) override;

        QHBoxLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QHBoxLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
