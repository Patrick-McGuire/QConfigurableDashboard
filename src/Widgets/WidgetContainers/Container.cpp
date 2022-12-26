#include <Container.h>

namespace QCD {

    Container::Container() : Widget() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        this->setLayout(m_layout);
        m_wrapperWidget = new QWidget(this);
        m_layout->addWidget(m_wrapperWidget);
    }

    bool Container::registerChildWidget(Widget *a_childWidget) {
        if (a_childWidget != nullptr && std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget) == m_childWidgets.end()) {
            m_childWidgets.push_back(a_childWidget);
            a_childWidget->setParent(m_wrapperWidget);
            return true;
        }
        return false;
    }

    bool Container::removeChildWidget(Widget *a_childWidget) {
        auto it = std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget);
        if (it != m_childWidgets.end()) {
            m_childWidgets.erase(it);
            return true;
        }
        return false;
    }

    void Container::onRun() {
        for (auto &childWidget: m_childWidgets) {
            childWidget->setGuiManager(m_appManager);
            childWidget->run();
        }
    }

    void Container::onUpdate(QCD::WidgetFocus a_focus) {
        bool inFocus = isInFocus(a_focus);
        for (auto &childWidget: m_childWidgets) {
            childWidget->smartUpdate(inFocus);
        }
    }

    bool Container::addWidget(Widget *a_baseWidget) {
        return false;
    }

} // QCD