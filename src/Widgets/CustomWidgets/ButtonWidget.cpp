
#include <iostream>
#include "ButtonWidget.h"

namespace QCD {
    ButtonWidget::ButtonWidget(const QString &a_text) : BaseWidget() {
        // Configure widget
        disableBorder();
        // Construct members
        m_layout = new QVBoxLayout();
        m_layout->setMargin(0);
        setLayout(m_layout);
        m_pushButton = new QPushButton(a_text, this);
        connect(m_pushButton, SIGNAL(pressed()), this, SLOT(onClick()));
        connect(m_pushButton, SIGNAL(released()), this, SLOT(onRelease()));
        m_layout->addWidget(m_pushButton);

        registerTheme(m_pushButton, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_pushButton, TEXT_COLOR_CLASS);

        adjustSize();
    }

    void ButtonWidget::onClick() {
        m_state = true;
        std::cout << "Clicked" << "\n";
        std::string a = "";
        if(m_dataPasser->getInputData().contains("KEY1") && m_dataPasser->getInputData()["KEY1"].is_string()) {
            a = m_dataPasser->getInputData()["KEY1"].get<std::string>();
        }
        m_dataPasser->getInputData()["KEY1"] = "adsf" + a;
    }

    void ButtonWidget::onRelease() {
        m_state = false;
        std::cout << "Released" << "\n";
    }
}


