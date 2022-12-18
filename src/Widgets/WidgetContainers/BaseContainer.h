#ifndef QCONFIGURABLEDASHBOARD_BASECONTAINER_H
#define QCONFIGURABLEDASHBOARD_BASECONTAINER_H

#include "../BaseWidget.h"
#include "vector"

namespace QCD {
    class BaseContainer : public BaseWidget {
    Q_OBJECT
    public:
        BaseContainer();

    protected:
        bool registerChildWidget(BaseWidget *a_childWidget);

        bool removeChildWidget(BaseWidget *a_childWidget);

        void onRun() override;
        std::vector<BaseWidget*> m_childWidgets;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASECONTAINER_H
