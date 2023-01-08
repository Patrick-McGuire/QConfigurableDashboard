#ifndef QCONFIGURABLEDASHBOARD_TABCONTAINER_H
#define QCONFIGURABLEDASHBOARD_TABCONTAINER_H

#include "Container.h"
#include "QTabWidget"
#include "QVBoxLayout"

namespace QCD {
    /**
     * @class TabContainer
     * @brief Widget that acts like a QTabWidget
     * @details Stores widgets in tabs, using a QTabWidget.
     * @see QCD::Container
     */
    class TabContainer : public Container {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit TabContainer();

        /**
         * @brief Adds a widget
         * @details Adds a new tab
         * @param a_baseWidget QCD::Widget to add
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget) override;

        /**
         * @brief Adds a widget
         * @details Adds a new tab
         * @param a_baseWidget QCD::Widget to add
         * @param a_name name/title of tab
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget, const QString &a_name);

        /**
         * @brief Returns the QT tab object
         * @details This lets you directly modify the QT tab object (be careful!)
         * @return QT tab object
         */
        QTabWidget *getTabs();

    protected:
        /**
         * @brief Updates all child widgets
         * @details Forwards call on to all child widgets
         * @param a_focus if this widget is in focus
         */
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QVBoxLayout *m_layout;              ///< Internally used layout
        QTabWidget *m_tabs;                 ///< QT tab object
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TABCONTAINER_H
