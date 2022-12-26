#include "HBoxContainer.h"

namespace QCD {
    HBoxContainer::HBoxContainer() {
        m_layout = new QHBoxLayout();
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool HBoxContainer::addWidget(Widget *a_baseWidget) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            m_layout->addWidget(a_baseWidget);
            a_baseWidget->disableFloating();
        }
        return added;
    }

    void HBoxContainer::onUpdate(QCD::WidgetFocus a_focus) {
        Container::onUpdate(a_focus);
        if(!m_inLayout) {
            adjustSize();
        }
    }

    QHBoxLayout *HBoxContainer::getLayout() {
        return m_layout;
    }
} // QCD