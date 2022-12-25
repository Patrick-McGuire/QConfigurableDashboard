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
#include "Core/AppManager.h"
#include "Interfaces/BaseInterface.h"
#include "Util/UtilFuntions.h"
#include "boost/circular_buffer.hpp"


namespace QCD {
    class QConfigurableDashboard : QObject {
    Q_OBJECT
    public:
        QConfigurableDashboard(int a_argc, char **a_argv, double a_rate = 30);

        ~QConfigurableDashboard() override;

        int run();

        bool setCentralWidget(BaseWidget *a_widget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

        bool addInterface(BaseInterface *a_baseInterface);

        QMenu *addMenu(const QString &a_name, const QString &a_parentName = "none");

        QAction *addMenuAction(const QString &a_name, const QString &a_parentName = "none");

        void updateTheme(const QString &a_activeTheme);

        static QString getClassStylesheet(const QString &a_class, const QString &a_style);

        QString getThemeData(const QString &a_themeName, const QString &a_attribute);

        void setUpdateAlways(bool a_updateAlways);

        void setAutoScale(bool a_autoScale);

        AppManager *getAppManager();

    public slots:

        void updateTheme(QAction *a_action);

    private slots:
        void updateDragging(QAction *a_action);

        void updateGUI();

    private:
        QMenu *findMenu(const QString &a_name);

        // Things
        int m_argc;
        char **m_argv;
        bool m_updateAlways = true;
        bool m_autoScale = false;
        double m_lastTime = 0;
        double m_desiredRate;
        double m_currentRate;
        // Core objects
        QApplication *m_qApplication;
        QMainWindow *m_mainWindow;
        QWidget *m_window;
        QVBoxLayout *m_layout;
        QTimer *m_timer;
        std::vector<QMenu *> m_menus;
        // Custom objects
        AppManager *m_appManager;
        BaseWidget *m_centralWidget;
        std::vector<BaseInterface *> m_interfaces;
        boost::circular_buffer<double> m_times = boost::circular_buffer<double>(100);
    };

}


#endif //ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H
