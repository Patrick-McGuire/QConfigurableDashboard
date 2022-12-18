#include <iostream>
#include "LineDisplayWidget.h"

namespace QCD {
    LineDisplayWidget::LineDisplayWidget() {
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        setLayout(m_layout);
        m_textBox = new QLabel("U suck");
        m_layout->addWidget(m_textBox);
        adjustSize();
    }

    void LineDisplayWidget::onUpdate(QCD::WidgetFocus focus) {
        if (focus == QCD::WidgetFocus::ON_IN_FOCUS || focus == QCD::WidgetFocus::IN_FOCUS) {
            if(m_guiManager->getInputData().contains("KEY1") && m_guiManager->getInputData()["KEY1"].is_string()) {
                m_textBox->setText(m_guiManager->getInputData()["KEY1"].get<std::string>().c_str());
                adjustSize();
            }
        }
    }

} // QCD