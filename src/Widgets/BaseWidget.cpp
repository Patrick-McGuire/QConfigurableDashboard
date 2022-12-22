#include <QPainter>
#include <iostream>
#include "BaseWidget.h"
#include "QFrame"

namespace QCD {

    BaseWidget::BaseWidget() : QFrame() {

    }

    void BaseWidget::run() {
        onRun();
    }

    void BaseWidget::onRun() {}

    void BaseWidget::smartUpdate(bool a_inFocus) {
        // Provide a scalar to the global onUpdate rate (run every nth time)
        m_updateCounter--;
        if (m_updateCounter <= 0) {
            m_updateCounter = m_updateRateScale;
            if (a_inFocus && m_lastFocus) {
                onUpdate(WidgetFocus::IN_FOCUS);
            } else if (!a_inFocus && !m_lastFocus) {
                onUpdate(WidgetFocus::NO_FOCUS);
            } else if (a_inFocus && !m_lastFocus) {
                onUpdate(WidgetFocus::ON_IN_FOCUS);
            } else if (!a_inFocus && m_lastFocus) {
                onUpdate(WidgetFocus::ON_NO_FOCUS);
            }
            m_lastFocus = a_inFocus;
        }
    }

    void BaseWidget::onUpdate(WidgetFocus a_focus) {}

    void BaseWidget::mouseMoveEvent(QMouseEvent *a_event) {
        if (m_clicked && m_dataPasser->getDraggingEnabled() && !m_staticPos) {
            move(a_event->globalX() - m_eventDragStartX + m_dragStartX, a_event->globalY() - m_eventDragStartY + m_dragStartY);
        }
    }

    void BaseWidget::mouseReleaseEvent(QMouseEvent *a_event) {
        if (!m_staticPos) {
            m_clicked = false;
            m_eventDragStartX = a_event->globalX();
            m_eventDragStartY = a_event->globalY();
        }
    }

    void BaseWidget::mousePressEvent(QMouseEvent *a_event) {
        if (!m_staticPos && m_dataPasser->getDraggingEnabled()) {
            m_clicked = true;
            m_eventDragStartX = a_event->globalX();
            m_eventDragStartY = a_event->globalY();
            m_dragStartX = x();
            m_dragStartY = y();
        }
    }

    void BaseWidget::disableFloating() {
        m_staticPos = true;
    }

    void BaseWidget::enableFloating() {
        m_staticPos = false;
    }

    void BaseWidget::disableBorder() {
        m_drawBorder = false;
    }

    bool BaseWidget::setUpdateRateScale(int a_scale) {
        if (a_scale >= 1) {
            m_updateRateScale = a_scale;
            m_updateCounter = m_updateRateScale;
            return true;
        }
        return false;
    }

    void BaseWidget::setGuiManager(DataPasser *a_guiManager) {
        m_dataPasser = a_guiManager;
    }

    void BaseWidget::registerTheme(QWidget *a_widget, const QString &attribute) {
        QString currentProperties = a_widget->property(THEME_PROPERTY).toString();
        if (currentProperties == "") {
            a_widget->setProperty(THEME_PROPERTY, attribute);
        } else {
            a_widget->setProperty(THEME_PROPERTY, currentProperties + " " + attribute);
        }
    }

    bool BaseWidget::isInFocus(WidgetFocus a_focus) {
        return a_focus == WidgetFocus::IN_FOCUS || a_focus == WidgetFocus::ON_IN_FOCUS;
    }
}