#ifndef QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
#define QCONFIGURABLEDASHBOARD_PANELCONTAINER_H

#include <QPainter>
#include <QVBoxLayout>
#include "vector"
#include "../Widget.h"
#include "../../Core/QCD.h"
#include "Container.h"

namespace QCD {
    class PanelContainer : public Container {
    Q_OBJECT
    public:
        explicit PanelContainer();

        bool addWidget(Widget *a_baseWidget) override;

        bool addWidget(Widget *a_baseWidget, int a_x, int a_y);

        bool setBackgroundWidget(Widget *a_baseWidget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

    protected:
        // QT Members
        QVBoxLayout *m_layout;
        // Custom members
        Widget *m_backgroundWidget = nullptr;
    };
}


#endif //QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
