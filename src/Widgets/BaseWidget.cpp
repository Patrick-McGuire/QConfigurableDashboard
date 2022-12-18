#include <QPainter>
#include "BaseWidget.h"

QCD::BaseWidget::BaseWidget() : QWidget() {

}

void QCD::BaseWidget::run() {
    onRun();
}

void QCD::BaseWidget::onRun() {}

void QCD::BaseWidget::smartUpdate(bool a_inFocus) {
    // Provide a scalar to the global update rate (run every nth time)
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

void QCD::BaseWidget::onUpdate(QCD::WidgetFocus a_focus) {}

void QCD::BaseWidget::mouseMoveEvent(QMouseEvent *a_event) {
    if (m_clicked && m_guiManager->getDraggingEnabled() && !m_staticPos) {
        move(a_event->globalX() - m_eventDragStartX + m_dragStartX, a_event->globalY() - m_eventDragStartY + m_dragStartY);
    }
}

void QCD::BaseWidget::mouseReleaseEvent(QMouseEvent *a_event) {
    if (!m_staticPos) {
        m_clicked = false;
        m_eventDragStartX = a_event->globalX();
        m_eventDragStartY = a_event->globalY();
    }
}

void QCD::BaseWidget::mousePressEvent(QMouseEvent *a_event) {
    if (!m_staticPos && m_guiManager->getDraggingEnabled()) {
        m_clicked = true;
        m_eventDragStartX = a_event->globalX();
        m_eventDragStartY = a_event->globalY();
        m_dragStartX = x();
        m_dragStartY = y();
    }
}

void QCD::BaseWidget::disableFloating() {
    m_staticPos = true;
}

void QCD::BaseWidget::enableFloating() {
    m_staticPos = false;
}

void QCD::BaseWidget::paintEvent(QPaintEvent *a_event) {
    QWidget::paintEvent(a_event);
    if (m_drawBorder) {
        QPainter painter(this);
        painter.drawRect(2, 2, width() - 5, height() - 5);
    }
}

void QCD::BaseWidget::disableBorder() {
    m_drawBorder = false;
}

bool QCD::BaseWidget::setUpdateRateScale(int a_scale) {
    if (a_scale >= 1) {
        m_updateRateScale = a_scale;
        m_updateCounter = m_updateRateScale;
        return true;
    }
    return false;
}

void QCD::BaseWidget::setGuiManager(QCD::GuiManager *a_guiManager) {
    m_guiManager = a_guiManager;
}


