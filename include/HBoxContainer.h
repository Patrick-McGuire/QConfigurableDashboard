#ifndef QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H

#include "Container.h"
#include "QHBoxLayout"

namespace QCD {
    /**
     * @class HBoxContainer
     * @brief Widget that acts like a QHBoxLayout
     * @details Stores widgets in a horizontal list format, using a QHBoxLayout.
     * @see QCD::Container
     */
    class HBoxContainer : public Container {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit HBoxContainer();

        /**
         * @brief Adds a widget
         * @details Adds a widget into the layout. Adds left to right
         * @param a_baseWidget QCD::Widget to add
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget) override;

        /**
         * @brief Returns the QT layout object
         * @details This lets you directly modify the QT layout (be careful!)
         * @return QT layout object
         */
        QHBoxLayout *getLayout();

    protected:
        /**
         * @brief Updates all child widgets
         * @details Forwards call on to all child widgets
         * @param a_focus if this widget is in focus
         */
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QHBoxLayout *m_layout;                                  ///< QT layout object
    };
} // QCD

#endif //QCONFIGURABLEDASHBOARD_HBOXCONTAINER_H
