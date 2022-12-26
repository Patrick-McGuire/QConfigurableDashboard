#ifndef QCONFIGURABLEDASHBOARD_TABCONTAINER_H
#define QCONFIGURABLEDASHBOARD_TABCONTAINER_H

#include "Container.h"
#include "QTabWidget"
#include "QVBoxLayout"

namespace QCD {

    class TabContainer : public Container {
        Q_OBJECT
    public:
        explicit TabContainer();

        bool addWidget(Widget *a_baseWidget) override;

        bool addWidget(Widget *a_baseWidget, const QString &a_name);

        QTabWidget *getTabs();

    protected:
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QVBoxLayout *m_layout;
        QTabWidget *m_tabs;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TABCONTAINER_H
