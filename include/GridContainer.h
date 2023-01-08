#ifndef QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
#define QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H

#include "Container.h"
#include "QGridLayout"

namespace QCD {
    /**
     * @class GridContainer
     * @brief Widget that acts like a QGridLayout
     * @details Stores widgets in a grid format, using a QGridLayout.
     * @see QCD::Container
     */
    class GridContainer : public Container {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit GridContainer();

        /**
         * @brief Adds a widget
         * @details Adds a widget into the layout
         * @param a_baseWidget QCD::Widget to add
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget) override;

        /**
         * @brief Adds a widget
         * @details Adds a widget at a given position into the layout
         * @param a_baseWidget QCD::Widget to add
         * @param a_row Row to insert to
         * @param a_col Column to insert to
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget, int a_row, int a_col);

        /**
         * @brief Returns the QT layout object
         * @details This lets you directly modify the QT layout (be careful!)
         * @return QT layout object
         */
        QGridLayout *getLayout();

    protected:
        /**
         * @brief Updates all child widgets
         * @details Forwards call on to all child widgets
         * @param a_focus if this widget is in focus
         */
        void onUpdate(QCD::WidgetFocus a_focus) override;

        QGridLayout *m_layout;                                      ///< QT layout object
    };
} // QCD

#endif //QCONFIGURABLEDASHBOARD_GRIDCONTAINER_H
