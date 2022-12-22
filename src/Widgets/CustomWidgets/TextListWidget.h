#ifndef QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H
#define QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include "../BaseWidget.h"

namespace QCD {

    class TextListWidget : public BaseWidget {
    Q_OBJECT
    public:
        explicit TextListWidget(const std::string &a_title = "");

        void listen(const std::string &a_key, const std::string &a_header);

    private:
        struct Line {
            std::string key;
            std::string header;
        };

        void onUpdate(QCD::WidgetFocus a_focus) override;

        QVBoxLayout *m_layout;
        QLabel *m_titleBox;
        QLabel *m_textBox;
        std::vector<Line> m_lines;
        std::string m_text;

        static const int m_ringSize = 10;
        int m_ringIndex = 0;
        int m_sizeRingBuffer[m_ringSize];

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H
