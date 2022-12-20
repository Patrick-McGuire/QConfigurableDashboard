#include "GridContainer.h"

namespace QCD {
    GridContainer::GridContainer() : BaseContainer() {
        m_layout = new QGridLayout;
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool GridContainer::addWidget(BaseWidget *a_baseWidget, int a_row, int a_col) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            m_layout->addWidget(a_baseWidget, a_row, a_col);
            a_baseWidget->disableFloating();
        }
        return added;
    }

    void GridContainer::onUpdate(QCD::WidgetFocus a_focus) {
        BaseContainer::onUpdate(a_focus);
        adjustSize();
    }

    QGridLayout *GridContainer::getLayout() {
        return m_layout;
    }
} // QCD