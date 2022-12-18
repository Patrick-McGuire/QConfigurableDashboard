#include "QConfigurableDashboard.h"

QCD::QConfigurableDashboard::QConfigurableDashboard(int a_argc, char **a_argv) {
    // Save these because why not
    m_argv = a_argv;
    m_argc = a_argc;
    // Construct core objects
    m_qApplication = new QApplication(m_argc, m_argv);
    m_mainWindow = new QMainWindow();
    m_window = new QWidget();
    m_layout = new QVBoxLayout();
    m_layout->setMargin(0);
    m_window->setLayout(m_layout);
    m_mainWindow->setCentralWidget(m_window);
    m_mainWindow->show();
    m_window->show();
    timer = new QTimer(this);
    // Leave null for now;
    m_centralWidget = nullptr;
    m_guiManager = new GuiManager();
}

int QCD::QConfigurableDashboard::run() {
    m_centralWidget->run();

    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
    timer->start(100);

    // Runs QT main loop
    int out = QApplication::exec();

    return out;
}

bool QCD::QConfigurableDashboard::setCentralWidget(QCD::BaseWidget *a_widget, QFlags<Qt::AlignmentFlag> a_alignment) {
    if (a_widget != nullptr) {
        m_layout->removeWidget(m_centralWidget);
        delete m_centralWidget;
        m_layout->addWidget(a_widget, 0, a_alignment);
        m_centralWidget = a_widget;
        m_centralWidget->disableFloating();
        m_centralWidget->setGuiManager(m_guiManager);
        return true;
    }
    return false;
}

void QCD::QConfigurableDashboard::updateGUI() {
    m_centralWidget->smartUpdate(true);
}
