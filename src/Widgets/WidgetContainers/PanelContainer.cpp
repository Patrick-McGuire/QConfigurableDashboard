#include "PanelContainer.h"
#include "QPushButton"

namespace QCD {
    PanelContainer::PanelContainer() : BaseContainer() {
        // Configure widget
        disableBorder();
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    void PanelContainer::onUpdate(WidgetFocus focus) {
        bool inFocus = isInFocus(focus);
        for (auto &childWidget: m_childWidgets) {
            childWidget->smartUpdate(inFocus);
        }
    }

    bool PanelContainer::addWidget(BaseWidget *baseWidget, int x, int y) {
        bool added = registerChildWidget(baseWidget);
        if (added) baseWidget->move(x, y);
        return added;
    }

    bool PanelContainer::setBackgroundWidget(BaseWidget *baseWidget, QFlags<Qt::AlignmentFlag> alignment) {
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
}


