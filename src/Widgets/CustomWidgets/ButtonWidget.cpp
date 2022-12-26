
#include <iostream>
#include "../../../include/ButtonWidget.h"

namespace QCD {
    ButtonWidget::ButtonWidget(const QString &a_text) : Widget() {
        // Configure widget
        disableBorder();
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(2);
        setLayout(m_layout);
        m_pushButton = new QPushButton(a_text, this);
        connect(m_pushButton, SIGNAL(pressed()), this, SLOT(onClick()));
        connect(m_pushButton, SIGNAL(released()), this, SLOT(onRelease()));
        connect(m_pushButton, SIGNAL(pressed()), this, SIGNAL(pressed()));
        connect(m_pushButton, SIGNAL(released()), this, SIGNAL(released()));
        m_layout->addWidget(m_pushButton);

        registerTheme(m_pushButton, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_pushButton, TEXT_COLOR_CLASS);

        adjustSize();
    }

    void ButtonWidget::onClick() {
        m_state = true;
        m_appManager->triggerCallback(m_outputKey);
    }

    void ButtonWidget::onRelease() {
        m_state = false;
        m_appManager->triggerCallback(m_outputKey2);
    }

    void ButtonWidget::publishTo(const std::string &a_key, bool onClick) {
        if(onClick) {
            m_outputKey = a_key;
        } else {
            m_outputKey2 = a_key;
        }
    }
}


