#include "BaseContainer.h"

namespace QCD {

    BaseContainer::BaseContainer() : BaseWidget() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        this->setLayout(m_layout);
        m_wrapperWidget = new QWidget(this);
        m_layout->addWidget(m_wrapperWidget);
    }

    bool BaseContainer::registerChildWidget(BaseWidget *a_childWidget) {
        if (a_childWidget != nullptr && std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget) == m_childWidgets.end()) {
            m_childWidgets.push_back(a_childWidget);
            a_childWidget->setParent(m_wrapperWidget);
            return true;
        }
        return false;
    }

    bool BaseContainer::removeChildWidget(BaseWidget *a_childWidget) {
        auto it = std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget);
        if (it != m_childWidgets.end()) {
            m_childWidgets.erase(it);
            return true;
        }
        return false;
    }

    void BaseContainer::onRun() {
        for (auto &childWidget: m_childWidgets) {
            childWidget->setGuiManager(m_guiManager);
            childWidget->run();
        }
    }

    bool BaseContainer::isInFocus(QCD::WidgetFocus a_focus) {
        return a_focus == QCD::WidgetFocus::IN_FOCUS || a_focus == QCD::WidgetFocus::ON_IN_FOCUS;
    }

    void BaseContainer::onUpdate(QCD::WidgetFocus a_focus) {
        bool inFocus = isInFocus(a_focus);
        for (auto &childWidget: m_childWidgets) {
            childWidget->smartUpdate(inFocus);
        }
    }

    bool BaseContainer::addWidget(BaseWidget *a_baseWidget) {
        return false;
    }

} // QCD