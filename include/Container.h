#ifndef QCONFIGURABLEDASHBOARD_CONTAINER_H
#define QCONFIGURABLEDASHBOARD_CONTAINER_H

#include <QVBoxLayout>
#include "Widget.h"
#include "vector"

namespace QCD {
    class Container : public Widget {
    Q_OBJECT
    public:
        Container();

        virtual bool addWidget(Widget *a_baseWidget);

    protected:
        void onUpdate(QCD::WidgetFocus a_focus) override;

        bool registerChildWidget(Widget *a_childWidget);

        bool removeChildWidget(Widget *a_childWidget);

        void onRun() override;

        std::vector<Widget*> m_childWidgets;
        // QT Members
        QWidget *m_wrapperWidget;

    private:
        QVBoxLayout *m_layout;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_CONTAINER_H
