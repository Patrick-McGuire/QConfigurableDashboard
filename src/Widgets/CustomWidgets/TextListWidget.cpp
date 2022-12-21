#include "TextListWidget.h"

namespace QCD {
    TextListWidget::TextListWidget(const std::string &title) : BaseWidget() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(5);
        setLayout(m_layout);
        m_titleBox = new QLabel(title.c_str());
        m_textBox = new QLabel("No data");
        m_layout->addWidget(m_titleBox);
        m_layout->addWidget(m_textBox);
        // Set up theme
        registerTheme(m_titleBox, TITLE_TEXT_COLOR_CLASS);
        registerTheme(m_textBox, TEXT_COLOR_CLASS);
        registerTheme(this, WIDGET_BACKGROUND_CLASS);
        registerTheme(this, BORDER_COLOR_CLASS);
    }

    void TextListWidget::listen(const std::string &key, const std::string &header) {
        m_lines.push_back({key, header});
    }

    void TextListWidget::onUpdate(QCD::WidgetFocus focus) {
        if(isInFocus(focus)) {
            m_text = "";
            for(auto & line : m_lines) {
                Json &jsonVal = m_guiManager->getInputData()[line.key];
                if(jsonVal.is_string()) {
                    m_text += line.header + ":\t" + jsonVal.get_ref<std::string&>() + "\n";
                } else if(jsonVal.is_number_float()) {
                    m_text += line.header + ":\t" + std::to_string(jsonVal.get<double>()) + "\n";
                } else if(jsonVal.is_number_integer()) {
                    m_text += line.header + ":\t" + std::to_string(jsonVal.get<int>()) + "\n";
                }
            }
            m_text.pop_back();
            m_textBox->setText(m_text.c_str());
        }
        adjustSize();
    }
} // QCD