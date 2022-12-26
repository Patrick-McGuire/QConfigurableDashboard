#include <iostream>
#include "../../../include/LineDisplayWidget.h"

namespace QCD {
    LineDisplayWidget::LineDisplayWidget(const std::string &a_key) {
        m_key = a_key;
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        setLayout(m_layout);
        m_textBox = new QLabel("U suck");
        m_layout->addWidget(m_textBox);
        adjustSize();

        registerTheme(m_textBox, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_textBox, TEXT_COLOR_CLASS);
    }

    void LineDisplayWidget::onUpdate(QCD::WidgetFocus a_focus) {
        if (a_focus == QCD::WidgetFocus::ON_IN_FOCUS || a_focus == QCD::WidgetFocus::IN_FOCUS) {
            Json &dataJsonValue = m_appManager->getInputData()[m_key];
            if (dataJsonValue.is_string()) {
                m_textBox->setText(dataJsonValue.get_ref<std::string &>().c_str());
            } else if (dataJsonValue.is_number_integer()) {
                m_textBox->setText(QString::number(dataJsonValue.get<int>()));
            } else if (dataJsonValue.is_number_float()) {
                m_textBox->setText(QString::number(dataJsonValue.get<double>()));
            }
            if(!m_inLayout) {
                adjustSize();
            }
        }
    }

    void LineDisplayWidget::listen(const std::string &a_key) {
        m_key = a_key;
    }

} // QCD