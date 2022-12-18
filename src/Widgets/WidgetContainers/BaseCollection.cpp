#include "BaseCollection.h"

namespace QCD {

    BaseCollection::BaseCollection() : BaseWidget() {}

    bool BaseCollection::registerChildWidget(BaseWidget *a_childWidget) {
        if (a_childWidget != nullptr && std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget) == m_childWidgets.end()) {
            m_childWidgets.push_back(a_childWidget);
            a_childWidget->setParent(this);
            return true;
        }
        return false;
    }

    bool BaseCollection::removeChildWidget(BaseWidget *a_childWidget) {
        auto it = std::find(m_childWidgets.begin(), m_childWidgets.end(), a_childWidget);
        if (it != m_childWidgets.end()) {
            m_childWidgets.erase(it);
            return true;
        }
        return false;
    }

    void BaseCollection::onRun() {
        for (auto &childWidget: m_childWidgets) {
            childWidget->setGuiManager(m_guiManager);
            childWidget->run();
        }
    }

} // QCD