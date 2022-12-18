/**
 * @brief Main class that runs the QApplication
 * @author Patrick-McGuire
 */
#ifndef ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H
#define ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H

// QT Includes
#include <QObject>
#include <QVBoxLayout>
#include "QApplication"
#include "QMainWindow"
#include "QTimer"
// Personal includes
#include "QCD.h"
#include "Widgets/BaseWidget.h"
#include "GuiManager.h"


namespace QCD {
    class QConfigurableDashboard : QObject {
    Q_OBJECT
    public:
        QConfigurableDashboard(int argc, char **argv);

        int run();

        bool setCentralWidget(BaseWidget *widget, QFlags<Qt::AlignmentFlag> alignment = Qt::Alignment());

    private slots:
        void updateGUI();

    private:

        // Things
        int m_argc;
        char **m_argv;
        // Core objects
        QApplication *m_qApplication;
        QMainWindow *m_mainWindow;
        QWidget *m_window;
        QVBoxLayout *m_layout;
        QTimer *timer;
        // Custom objects
        GuiManager *m_guiManager;
        BaseWidget *m_centralWidget;
    };

}


#endif //ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H
