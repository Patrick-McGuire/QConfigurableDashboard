#ifndef QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H

#include "BaseContainer.h"
#include "QHBoxLayout"

namespace QCD {

    class HBoxContainer : public BaseContainer {
    Q_OBJECT
    public:
        explicit HBoxContainer();

        bool addWidget(BaseWidget *a_baseWidget) override;

        QHBoxLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QHBoxLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
