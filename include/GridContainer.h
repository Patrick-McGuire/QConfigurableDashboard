#ifndef QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
#define QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H

#include "Container.h"
#include "QGridLayout"

namespace QCD {

    class GridContainer : public Container {
    Q_OBJECT
    public:
        explicit GridContainer();

        bool addWidget(Widget *a_baseWidget) override;

        bool addWidget(Widget *a_baseWidget, int a_row, int a_col);

        QGridLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QGridLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
