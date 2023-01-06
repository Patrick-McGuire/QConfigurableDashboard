#ifndef QCONFIGURABLEDASHBOARD_TABMODULE_H
#define QCONFIGURABLEDASHBOARD_TABMODULE_H

#include <Module.h>
#include <TabContainer.h>
#include <Widget.h>
#include <Container.h>

namespace QCD {

    class TabModule : public Module {
    Q_OBJECT
    public:
        TabModule();

        void addWidget(Widget *a_widget, const QString &a_tabName = "No name");

    protected:
        static TabContainer *m_tabs;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TABMODULE_H
