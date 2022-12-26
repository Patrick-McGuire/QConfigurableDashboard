#include <QFileDialog>
#include <VideoRecorderWidget.h>

namespace QCD {
    VideoRecorderWidget::VideoRecorderWidget() {
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        m_layout = new QVBoxLayout();
        m_layout->setMargin(5);
        setLayout(m_layout);
        m_title = new QLabel("Video Recorder");
        m_layout->addWidget(m_title, 0, Qt::AlignHCenter);
//        m_layout->setAlignment(Qt::All)
        m_topWidget = new QWidget();
        m_layout->addWidget(m_topWidget);
        m_topLayout = new QHBoxLayout();
        m_topLayout->setMargin(0);
        m_topWidget->setLayout(m_topLayout);
        m_bottomWidget = new QWidget();
        m_layout->addWidget(m_bottomWidget);
        m_bottomLayout = new QHBoxLayout();
        m_bottomLayout->setMargin(0);
        m_bottomWidget->setLayout(m_bottomLayout);


        m_comboBox = new QComboBox();
        m_comboBox->addItem("Op1");
        m_comboBox->addItem("Op2");
        m_startButton = new QPushButton("Start recording");
        m_topLayout->addWidget(m_comboBox);
        m_topLayout->addWidget(m_startButton);

        m_filePathWidget = new QLineEdit();
        m_filePathWidget->setText("test12345678");
        m_fileSelect = new QPushButton("Select Directory");
        m_bottomLayout->addWidget(m_filePathWidget);
        m_bottomLayout->addWidget(m_fileSelect);
        m_filePathWidget->setMinimumWidth(200);

        registerTheme(m_title, TITLE_TEXT_COLOR_CLASS);
        registerTheme(m_startButton, TEXT_COLOR_CLASS);
        registerTheme(m_comboBox, TEXT_COLOR_CLASS);
        registerTheme(m_filePathWidget, TEXT_COLOR_CLASS);
        registerTheme(m_fileSelect, TEXT_COLOR_CLASS);

        registerTheme(m_title, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_startButton, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_comboBox, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_filePathWidget, WIDGET_BACKGROUND_CLASS);
        registerTheme(m_fileSelect, WIDGET_BACKGROUND_CLASS);

        registerTheme(this, WIDGET_BACKGROUND_CLASS);
        registerTheme(this, BORDER_COLOR_CLASS);

        adjustSize();

        connect(m_fileSelect, SIGNAL(pressed()), this, SLOT(getFolderLoc()));
        connect(m_startButton, SIGNAL(pressed()), this, SLOT(toggleRecording()));
    }

    void VideoRecorderWidget::getFolderLoc() {
        QString filePath = QFileDialog::getExistingDirectory(this, "Select Directory");
        if (!filePath.isEmpty()) {
            m_filePathWidget->setText(filePath);
        }

    }

    void VideoRecorderWidget::toggleRecording() {
        Json eventData = Json::object();
        eventData[VIDEO_RECORD_PATH_KEY] = m_filePathWidget->text().toStdString();
        eventData[VIDEO_RECORD_ID_KEY] = m_comboBox->currentText().toStdString();
        if(m_startButton->text() == "Stop recording") {
            m_startButton->setText("Start recording");
            eventData[VIDEO_RECORD_TYPE_KEY] = false;
        } else {
            m_startButton->setText("Stop recording");
            eventData[VIDEO_RECORD_TYPE_KEY] = true;
        }
        m_appManager->triggerCallback(VIDEO_RECORD_KEY, eventData);
    }

    void VideoRecorderWidget::onUpdate(QCD::WidgetFocus a_focus) {
        int i = 0;
        for (auto &el: m_appManager->getImageMap()) {
            if (i < m_comboBox->count()) {
                if(m_comboBox->itemText(i) != el.first.c_str()) {
                    m_comboBox->setItemText(i, el.first.c_str());
                }
            } else {
                m_comboBox->addItem(el.first.c_str());
            }
            i++;
        }
    }
} // QCD