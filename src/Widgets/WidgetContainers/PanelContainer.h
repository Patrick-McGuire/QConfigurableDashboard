#ifndef QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
#define QCONFIGURABLEDASHBOARD_PANELCONTAINER_H

#include <QPainter>
#include <QVBoxLayout>
#include "vector"
#include "../BaseWidget.h"
#include "../../QCD.h"
#include "BaseContainer.h"

namespace QCD {
    class PanelContainer : public BaseContainer {
    Q_OBJECT
    public:
        explicit PanelContainer();

        bool addWidget(BaseWidget *a_baseWidget, int a_x = 0, int a_y = 0);

        bool setBackgroundWidget(BaseWidget *a_baseWidget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

    protected:
        // QT Members
        QVBoxLayout *m_layout;
        // Custom members
        BaseWidget *m_backgroundWidget = nullptr;
    };
}


#endif //QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
