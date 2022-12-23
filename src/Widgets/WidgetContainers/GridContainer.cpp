#include "GridContainer.h"

namespace QCD {
    GridContainer::GridContainer() : BaseContainer() {
        m_layout = new QGridLayout;
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool GridContainer::addWidget(BaseWidget *a_baseWidget) {
        return addWidget(a_baseWidget, -1, -1);
    }

    bool GridContainer::addWidget(BaseWidget *a_baseWidget, int a_row, int a_col) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            if(a_row < 0 || a_col < 0) {
                m_layout->addWidget(a_baseWidget);
            } else {
                m_layout->addWidget(a_baseWidget, a_row, a_col);
            }
            a_baseWidget->disableFloating();
        }
        return added;
    }

    void GridContainer::onUpdate(QCD::WidgetFocus a_focus) {
        BaseContainer::onUpdate(a_focus);
        if(!m_inLayout) {
            adjustSize();
        }
    }

    QGridLayout *GridContainer::getLayout() {
        return m_layout;
    }
} // QCD