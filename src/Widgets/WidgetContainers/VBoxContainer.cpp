#include "VBoxContainer.h"

namespace QCD {
    VBoxContainer::VBoxContainer() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool VBoxContainer::addWidget(BaseWidget *a_baseWidget) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            m_layout->addWidget(a_baseWidget);
            a_baseWidget->disableFloating();
        }
        return added;
    }

    void VBoxContainer::onUpdate(QCD::WidgetFocus a_focus) {
        BaseContainer::onUpdate(a_focus);
        adjustSize();
    }

    QVBoxLayout *VBoxContainer::getLayout() {
        return m_layout;
    }
} // QCD