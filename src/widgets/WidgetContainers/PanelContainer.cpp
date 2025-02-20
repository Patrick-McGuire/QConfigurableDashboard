#include <QPushButton>
#include <PanelContainer.h>

namespace QCD {
    PanelContainer::PanelContainer() : Container() {
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool PanelContainer::addWidget(Widget *a_baseWidget) {
        return addWidget(a_baseWidget, 0, 0);
    }

    bool PanelContainer::addWidget(Widget *a_baseWidget, int a_x, int a_y) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            a_baseWidget->setInLayout(false);
            a_baseWidget->move(a_x, a_y);
        }
        return added;
    }

    bool PanelContainer::setBackgroundWidget(Widget *a_baseWidget, QFlags<Qt::AlignmentFlag> a_alignment) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            removeChildWidget(m_backgroundWidget);

            m_layout->removeWidget(m_backgroundWidget);
            delete m_backgroundWidget;
            m_backgroundWidget = a_baseWidget;
            m_layout->addWidget(a_baseWidget, 0, a_alignment);
            m_backgroundWidget->disableFloating();

            return true;
        }
        return false;

    }


}


