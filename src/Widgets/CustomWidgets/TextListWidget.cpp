#include <algorithm>
#include <TextListWidget.h>

namespace QCD {
    TextListWidget::TextListWidget(const std::string &a_title) : Widget() {
        m_layout = new QVBoxLayout();
        m_layout->setMargin(5);
        setLayout(m_layout);
        m_titleBox = new QLabel(a_title.c_str());
        m_textBox = new QLabel("No data");
        m_layout->addWidget(m_titleBox);
        m_layout->addWidget(m_textBox);
        // Set up theme
        registerTheme(m_titleBox, TITLE_TEXT_COLOR_CLASS);
        registerTheme(m_textBox, TEXT_COLOR_CLASS);
        registerTheme(this, WIDGET_BACKGROUND_CLASS);
        registerTheme(this, BORDER_COLOR_CLASS);

        for (auto &i: m_sizeRingBuffer) i = 0;      // Reset the ring buffer
//        m_textBox->sizeHint().
    }

    void TextListWidget::listen(const std::string &a_key, const std::string &a_header) {
        m_lines.push_back({a_key, a_header});
    }

    void TextListWidget::onUpdate(QCD::WidgetFocus a_focus) {
        if (isInFocus(a_focus)) {
            m_text = "";
            for (auto &line: m_lines) {
                Json &jsonVal = m_inputData[line.key];
                if (jsonVal.is_string()) {
                    m_text += line.header + ":\t" + jsonVal.get_ref<std::string &>() + "\n";
                } else if (jsonVal.is_number_float()) {
                    m_text += line.header + ":\t" + std::to_string(jsonVal.get<double>()) + "\n";
                } else if (jsonVal.is_number_integer()) {
                    m_text += line.header + ":\t" + std::to_string(jsonVal.get<int>()) + "\n";
                }
            }
            m_text.pop_back();
            m_textBox->setText(m_text.c_str());
        }
        // Ring buff to track when to auto shrink
        m_sizeRingBuffer[m_ringIndex] = std::max(m_textBox->sizeHint().width(), m_titleBox->sizeHint().width());
        m_ringIndex++;
        m_ringIndex = m_ringIndex % m_ringSize;
        int max = 0;
        for (int &i: m_sizeRingBuffer) max = std::max(max, i);
        // Correct size
        setMinimumWidth(max + 10);
        if(!m_inLayout) {
            adjustSize();
        }
    }
} // QCD