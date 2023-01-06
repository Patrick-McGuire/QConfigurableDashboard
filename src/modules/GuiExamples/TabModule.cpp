#include <TabModule.h>
#include <QConfigurableDashboard.h>
#include <LineDisplayWidget.h>

namespace QCD {
    TabContainer *TabModule::m_tabs = nullptr;

    TabModule::TabModule() {
        if(m_tabs == nullptr) {
            m_tabs = new TabContainer();
        }
        if(m_tabs != m_app->getCentralWidget()) {
            m_app->setCentralWidget(m_tabs);
        }
    }
} // QCD