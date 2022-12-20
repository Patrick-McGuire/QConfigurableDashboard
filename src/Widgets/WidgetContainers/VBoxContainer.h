#ifndef QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H

#include "BaseContainer.h"
#include "QVBoxLayout"

namespace QCD {

    class VBoxContainer : public BaseContainer {
    Q_OBJECT
    public:
        explicit VBoxContainer();

        bool addWidget(BaseWidget *a_baseWidget);

        QVBoxLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QVBoxLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
