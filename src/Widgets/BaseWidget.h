#ifndef ROBOT_GUI_V3_BASEWIDGET_H
#define ROBOT_GUI_V3_BASEWIDGET_H

#include "QWidget"
#include "../QCD.h"
#include "../GuiManager.h"
#include "QMouseEvent"

namespace QCD {
    class BaseWidget : public QWidget {
    Q_OBJECT
    public:
        explicit BaseWidget();

        virtual void run();

        void setGuiManager(GuiManager *a_guiManager);

        void smartUpdate(bool a_inFocus);

        void disableFloating();

        void enableFloating();

        void disableBorder();

        bool setUpdateRateScale(int a_scale);

    protected:
        virtual void onRun();

        virtual void onUpdate(WidgetFocus a_focus);

        GuiManager *m_guiManager;


    private:
        void paintEvent(QPaintEvent *a_event) override;

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