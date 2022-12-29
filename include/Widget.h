#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H

#include <CoreObject.h>
#include <QWidget>
#include <QCD.h>
#include <QMouseEvent>
#include <QFrame>

namespace QCD {
    /**
     * @class Widget
     * @brief Base class for all QCD custom widget.
     * @details This class handles all root functionality for QCD's custom widgets.
     * This includes dragging, themes and periodically being updated. This class should be the parent class for all custom widgets used in a QCD application.
     * @note m_appManager is not guaranteed to be populated before QCD::Widget::run() is called
     * @see QCD::Container These are QCD's re-implementations of QLayouts
     * @authors Patrick-McGuire
     */
    class Widget : public QFrame, public CoreObject {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         */
        explicit Widget();

        /**
         * @brief Finish initializing this widget
         * @details This is called when QCD::QConfigurableDashboard::run() is called, and this calls QCD::Widget::onRun().
         */
        int run() override;

        /**
         * @brief Updates this widget
         * @details Calls QCD::Widget::onUpdate() with the correct QCD::WidgetFocus, and provides proper runUpdate rate scaling as set by QCD::Widget::setUpdateRateScale().
         * @param a_inFocus if visible
         * @note This is handled internally, and should never be called outside of QCD's core classes.
         * @param a_inFocus if this widget is currently visible
         */
        void runUpdate(bool a_inFocus) override;

        /**
         * @brief Disables dragging for this widget
         * @note This is generally handled internally (by Containers), but can be used to prevent a widget from being dragged inside a QCD::PanelContainer.
         */
        void disableFloating();

        /**
         * @brief Enables dragging for this widget
         * @note This is generally handled internally (by Containers), but can be used to enable dragging for a widget inside a QCD::PanelContainer.
         */
        void enableFloating();

        /**
         * @brief Sets a multiplier on the application runUpdate rate specific to this widget
         * @details This will runUpdate this widget every nth QCD::Widget::runUpdate() call.
         * This can be used to improve performance on widgets that don't need to be updated frequently.
         * This may be re-implemented by derived classes, so it's behavior is not guaranteed on all derivations of QCD::Widget.
         * @param a_scale scale to set
         * @pre a_scale >= 1
         * @return if the scale was valid (if scale > 1)
         */
        virtual bool setUpdateRateScale(int a_scale);

        /**
         * @brief Add a CSS esque class property to a QWidget
         * @details TODO: Probably re-implementing
         * @param a_widget thing
         * @param attribute stuff
         */
        static void registerTheme(QWidget *a_widget, const QString &attribute);

        /**
         * @brief Set if this object is in a layout (vs just have a parent)
         * @note This is handled internally, and should never be called outside of QCD's core classes.
         * @param a_inLayout if in a layout
         */
        void setInLayout(bool a_inLayout);

    protected:
        /**
         * @brief Runs on Application startup
         * @details implemented in derived
         * @see QCD::Widget::run()
         */
        virtual void onRun();

        /**
         * @brief Runs when the Application updates
         * @details implemented in derived
         * @param a_focus if the widget is visible
         * @see QCD::Widget::runUpdate()
         * @see QCD::WidgetFocus
         */
        virtual void onUpdate(WidgetFocus a_focus);

        /**
         * @brief Determines if a WidgetFocus is currently visible
         * @param a_focus focus to check
         * @return if the widget is currently visible
         */
        static bool isInFocus(QCD::WidgetFocus a_focus);

        bool m_inLayout = true;                                 ///< Boolean that tracks if the widget is stored in a layout


    private:
        using CoreObject::m_app;                                // Don't let widgets mess with this

        void mousePressEvent(QMouseEvent *a_event) override;

        void mouseReleaseEvent(QMouseEvent *a_event) override;

        void mouseMoveEvent(QMouseEvent *a_event) override;

        int m_eventDragStartX = 0;
        int m_eventDragStartY = 0;
        int m_dragStartX = 0;
        int m_dragStartY = 0;
        int m_updateRateScale = 1;
        int m_updateCounter = 0;
        bool m_clicked = false;
        bool m_lastFocus = true;
        bool m_staticPos = false;
    };
}

#endif //ROBOT_GUI_V3_BASEWIDGET_H