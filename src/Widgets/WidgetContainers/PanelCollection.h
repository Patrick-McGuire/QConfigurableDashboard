#ifndef QCONFIGURABLEDASHBOARD_PANELCOLLECTION_H
#define QCONFIGURABLEDASHBOARD_PANELCOLLECTION_H

#include <QPainter>
#include <QVBoxLayout>
#include "vector"
#include "../BaseWidget.h"
#include "../../QCD.h"
#include "BaseCollection.h"

namespace QCD {
    class PanelCollection : public BaseCollection {
    Q_OBJECT
    public:
        explicit PanelCollection();


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


#endif //QCONFIGURABLEDASHBOARD_PANELCOLLECTION_H
