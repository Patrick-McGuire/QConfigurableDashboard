#ifndef QCONFIGURABLEDASHBOARD_CONTAINER_H
#define QCONFIGURABLEDASHBOARD_CONTAINER_H

#include <QVBoxLayout>
#include "Widget.h"
#include "vector"

namespace QCD {
    /**
     * @class Container
     * @brief Base class for all QCD containers
     * @details The goal of QCD containers is to remove the concept from QT of widgets having layouts
     * to encompass other widgets. Instead with QCD, layouts are just another type of QCD::Widget that
     * you can add children directly too.
     * @see QCD::Widget
     */
    class Container : public Widget {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        Container();

        /**
         * @brief Adds a widget to the layout
         * @details Pure virtual
         * @param a_baseWidget QCD::Widget to add
         * @return if widget was added
         */
        virtual bool addWidget(Widget *a_baseWidget) = 0;

    protected:
        /**
         * @brief Updates all child widgets
         * @details Calls QCD::Widget::runUpdate() on all child widgets
         * @param a_focus if this widget is in visible
         */
        void onUpdate(QCD::WidgetFocus a_focus) override;

        /**
         * @brief Adds a child widget to this
         * @details Call in derived anytime a widget is added to a container
         * @param a_childWidget QCD::Widget to add
         * @return if added successfully
         */
        bool registerChildWidget(Widget *a_childWidget);

        /**
         * @brief Removes a child widget from this
         * @brief Call in derived to deregister a widget
         * @param a_childWidget QCD::Widget to add
         * @return if removed successfully
         */
        bool removeChildWidget(Widget *a_childWidget);

        /**
         * @brief Runs the container
         * @details forwards run call on to all child classes
         */
        void onRun() override;

        std::vector<Widget*> m_childWidgets;                ///< List of all child widgets
        QWidget *m_wrapperWidget;                           ///< Widget used internally to get around QT weirdness

    private:
        QVBoxLayout *m_layout;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_CONTAINER_H
