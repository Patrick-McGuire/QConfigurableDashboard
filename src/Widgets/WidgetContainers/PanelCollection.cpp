#include "PanelCollection.h"
#include "QPushButton"

QCD::PanelCollection::PanelCollection() : BaseCollection() {
    // Configure widget
    disableBorder();
    // Construct members
    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    setLayout(m_layout);
}

void QCD::PanelCollection::onUpdate(QCD::WidgetFocus focus) {
    bool inFocus = focus == QCD::WidgetFocus::IN_FOCUS || focus == QCD::WidgetFocus::ON_IN_FOCUS;
    for (auto &childWidget: m_childWidgets) {
        childWidget->smartUpdate(inFocus);
    }
}

bool QCD::PanelCollection::addWidget(QCD::BaseWidget *baseWidget, int x, int y) {
    bool added = registerChildWidget(baseWidget);
    if (added) {
        baseWidget->move(x, y);
        return true;
    }
    return false;
}

bool QCD::PanelCollection::setBackgroundWidget(BaseWidget *baseWidget, QFlags<Qt::AlignmentFlag> alignment) {
    bool added = registerChildWidget(baseWidget);
    if (added) {
        removeChildWidget(m_backgroundWidget);

        m_layout->removeWidget(m_backgroundWidget);
        delete m_backgroundWidget;
        m_backgroundWidget = baseWidget;
        m_layout->addWidget(baseWidget, 0, alignment);
        m_backgroundWidget->disableFloating();

        return true;
    }
    return false;

}



