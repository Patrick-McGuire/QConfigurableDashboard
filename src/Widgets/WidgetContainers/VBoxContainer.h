#ifndef QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H

#include "Container.h"
#include "QVBoxLayout"

namespace QCD {

    class VBoxContainer : public Container {
    Q_OBJECT
    public:
        explicit VBoxContainer();

        bool addWidget(Widget *a_baseWidget) override;

        QVBoxLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QVBoxLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
