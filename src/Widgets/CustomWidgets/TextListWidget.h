#ifndef QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H
#define QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include "../BaseWidget.h"

namespace QCD {

    class TextListWidget : public BaseWidget {
    Q_OBJECT
    public:
        explicit TextListWidget(const std::string &title = "");

        void listen(const std::string &key, const std::string &header);

    private:
        struct Line {
            std::string key;
            std::string header;
        };

        void onUpdate(QCD::WidgetFocus focus) override;

        QVBoxLayout *m_layout;
        QLabel *m_titleBox;
        QLabel *m_textBox;
        std::vector<Line> m_lines;
        std::string m_text;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TEXTLISTWIDGET_H
