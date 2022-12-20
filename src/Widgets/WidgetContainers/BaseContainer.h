#ifndef QCONFIGURABLEDASHBOARD_BASECONTAINER_H
#define QCONFIGURABLEDASHBOARD_BASECONTAINER_H

#include <QVBoxLayout>
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

        static bool isInFocus(QCD::WidgetFocus focus);

        std::vector<BaseWidget*> m_childWidgets;
        // QT Members
        QWidget *m_wrapperWidget;

    private:
        QVBoxLayout *m_layout;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_BASECONTAINER_H
