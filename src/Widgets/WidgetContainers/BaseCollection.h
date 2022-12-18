#ifndef QCONFIGURABLEDASHBOARD_BASECOLLECTION_H
#define QCONFIGURABLEDASHBOARD_BASECOLLECTION_H

#include "../BaseWidget.h"
#include "vector"

namespace QCD {
    class BaseCollection : public BaseWidget {
    Q_OBJECT
    public:
        BaseCollection();

    protected:
        bool registerChildWidget(BaseWidget *a_childWidget);

        bool removeChildWidget(BaseWidget *a_childWidget);

        void onRun() override;
        std::vector<BaseWidget*> m_childWidgets;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASECOLLECTION_H
