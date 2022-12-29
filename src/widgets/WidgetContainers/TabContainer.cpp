#include <QSizePolicy>
#include <QTabBar>
#include <TabContainer.h>

namespace QCD {
    TabContainer::TabContainer() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        m_wrapperWidget->setLayout(m_layout);
        m_tabs = new QTabWidget();
        m_layout->addWidget(m_tabs);
        registerTheme(m_tabs, CONTAINER_BACKGROUND_CLASS);
        registerTheme(m_wrapperWidget, CONTAINER_BACKGROUND_CLASS);
    }

    bool TabContainer::addWidget(Widget *a_baseWidget) {
        return addWidget(a_baseWidget, "No name");
    }

    bool TabContainer::addWidget(Widget *a_baseWidget, const QString &a_name) {
        bool added = registerChildWidget(a_baseWidget);
        if (added) {
            m_tabs->addTab(a_baseWidget, a_name);
            a_baseWidget->disableFloating();
        };
        return added;
    }

    void TabContainer::onUpdate(QCD::WidgetFocus a_focus) {
        bool inFocus;
        for (auto &childWidget: m_childWidgets) {
            inFocus = isInFocus(a_focus) && childWidget == m_tabs->currentWidget();
            childWidget->runUpdate(inFocus);
        }
        if(!m_inLayout) {
            adjustSize();
        }
    }

    QTabWidget *TabContainer::getTabs() {
        return m_tabs;
    }
} // QCD