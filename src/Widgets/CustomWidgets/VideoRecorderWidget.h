#ifndef QCONFIGURABLEDASHBOARD_VIDEORECORDERWIDGET_H
#define QCONFIGURABLEDASHBOARD_VIDEORECORDERWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "../BaseWidget.h"
#include <QComboBox>
#include "QLineEdit"
#include "QPushButton"
#include "../../QCD.h"
namespace QCD {

    class VideoRecorderWidget : public BaseWidget {
        Q_OBJECT
    public:
        VideoRecorderWidget();

        void onUpdate(QCD::WidgetFocus a_focus) override;

    private slots:
        void getFolderLoc();

        void toggleRecording();
    private:
        QVBoxLayout *m_layout;
        QLabel *m_title;
        QWidget *m_topWidget;
        QHBoxLayout *m_topLayout;
        QWidget *m_bottomWidget;
        QHBoxLayout *m_bottomLayout;


        QComboBox *m_comboBox;
        QLineEdit *m_filePathWidget;
        QPushButton *m_startButton;
        QPushButton *m_fileSelect;

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_VIDEORECORDERWIDGET_H
