#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H

#include "QWidget"
#include "QCD.h"
#include "AppManager.h"
#include "QMouseEvent"
#include "QFrame"

namespace QCD {
    /**
     * @class Widget
     * @brief Base class for all widgets
     */
    class Widget : public QFrame {
    Q_OBJECT
    public:
        explicit Widget();

        virtual void run();

        void setGuiManager(AppManager *a_guiManager);

        void smartUpdate(bool a_inFocus);

        void disableFloating();

        void enableFloating();

        void disableBorder();

        virtual bool setUpdateRateScale(int a_scale);

        static void registerTheme(QWidget *a_widget, const QString &attribute);

        void setInLayout(bool a_inLayout);

    protected:
        virtual void onRun();

        virtual void onUpdate(WidgetFocus a_focus);

        static bool isInFocus(QCD::WidgetFocus a_focus);

        AppManager *m_appManager;
        bool m_inLayout = true;



    private:
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
        bool m_drawBorder = true;
    };
}

#endif //ROBOT_GUI_V3_BASEWIDGET_H