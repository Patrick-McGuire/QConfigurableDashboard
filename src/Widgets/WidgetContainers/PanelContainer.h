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


        bool addWidget(BaseWidget *baseWidget, int x = 0, int y = 0);

        bool setBackgroundWidget(BaseWidget *baseWidget, QFlags<Qt::AlignmentFlag> alignment = Qt::Alignment());

    protected:
        void onUpdate(QCD::WidgetFocus focus) override;

        // QT Members
        QVBoxLayout *m_layout;
        // Custom members
        BaseWidget *m_backgroundWidget = nullptr;
    };
}


#endif //QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
