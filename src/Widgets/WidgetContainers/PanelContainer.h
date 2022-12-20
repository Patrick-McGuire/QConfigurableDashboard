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

        bool addWidget(BaseWidget *a_baseWidget) override;

        bool addWidget(BaseWidget *a_baseWidget, int a_x, int a_y);

        bool setBackgroundWidget(BaseWidget *a_baseWidget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

    protected:
        // QT Members
        QVBoxLayout *m_layout;
        // Custom members
        BaseWidget *m_backgroundWidget = nullptr;
    };
}


#endif //QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
