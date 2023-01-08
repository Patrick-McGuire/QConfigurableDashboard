#ifndef QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
#define QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H

#include "Container.h"
#include "QVBoxLayout"

namespace QCD {
    /**
     * @class VBoxContainer
     * @brief Widget that acts like a QVBoxLayout
     * @details Stores widgets in a vertical list format, using a QVBoxLayout.
     * @see QCD::Container
     */
    class VBoxContainer : public Container {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit VBoxContainer();

        /**
         * @brief Adds a widget
         * @details Adds a widget into the layout. Adds top to bottom
         * @param a_baseWidget QCD::Widget to add
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget) override;

        /**
         * @brief Returns the QT layout object
         * @details This lets you directly modify the QT layout (be careful!)
         * @return QT layout object
         */
        QVBoxLayout *getLayout();

    protected:
        /**
         * @brief Updates all child widgets
         * @details Forwards call on to all child widgets
         * @param a_focus if this widget is in focus
         */
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QVBoxLayout *m_layout;                                  ///< QT layout object
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VBOXCONTAINER_H
