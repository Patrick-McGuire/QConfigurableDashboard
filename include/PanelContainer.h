#ifndef QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
#define QCONFIGURABLEDASHBOARD_PANELCONTAINER_H

#include <QPainter>
#include <QVBoxLayout>
#include "vector"
#include "Widget.h"
#include "QCD.h"
#include "Container.h"

namespace QCD {
    /**
     * @class PanelContainer
     * @brief Widget that allows you to specify absolute positions
     * @details Stores widgets is absolute (pixel) positions, and allows for dragging.
     * @see QCD::Container
     */
    class PanelContainer : public Container {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit PanelContainer();

        /**
         * @brief Adds a widget
         * @details Adds a widget into the panel
         * @param a_baseWidget QCD::Widget to add
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget) override;

        /**
         * @brief Adds a widget
         * @details Adds a widget into the panel
         * @param a_baseWidget QCD::Widget to add
         * @param a_x x position (pixels)
         * @param a_y y position (pixels)
         * @return if successful
         */
        bool addWidget(Widget *a_baseWidget, int a_x, int a_y);

        /**
         * @brief Sets the background for the entire panel
         * @param a_baseWidget Widget to be the background
         * @param a_alignment Optional: alignment of the widget
         * @return if successful
         */
        bool setBackgroundWidget(Widget *a_baseWidget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

    protected:
        QVBoxLayout *m_layout;                              ///< Internal layout object
        Widget *m_backgroundWidget = nullptr;               ///< Background widget pointer
    };
}


#endif //QCONFIGURABLEDASHBOARD_PANELCONTAINER_H
