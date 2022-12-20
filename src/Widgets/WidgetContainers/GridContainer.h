#ifndef QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
#define QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H

#include "BaseContainer.h"
#include "QGridLayout"

namespace QCD {

    class GridContainer : public BaseContainer {
    Q_OBJECT
    public:
        explicit GridContainer();

        bool addWidget(BaseWidget *a_baseWidget) override;

        bool addWidget(BaseWidget *a_baseWidget, int a_row, int a_col);

        QGridLayout *getLayout();

    protected:

        void onUpdate(QCD::WidgetFocus a_focus) override;

        // QT Members
        QGridLayout *m_layout;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
