#ifndef ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H
#define ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H

#include <boost/circular_buffer.hpp>
#include <QObject>
#include <QVBoxLayout>
#include "QApplication"
#include <QMainWindow>
#include <QTimer>
#include <QCD.h>
#include <Widget.h>
#include <AppManager.h>
#include <Module.h>
#include <UtilFunctions.h>

// @todo fix menu events
namespace QCD {
    class AppManager;   // Forward decl

    class Module;       // Forward decl

    /**
     * @brief Core class for running a QCD dashboard application
     * @details Handles updating data, menus, adding widgets, adding modules, changing themes and running the entire application.
     * This only has the ability to set 1 core widget. In most cases where many widgets are desired, set a QCD::Container as the central widget.
     * Then you can add as many widgets to the container as you like. Setting the central widget and creating widgets is best done from modules
     * but can also be done from the main funtion. Calling QCD::QConfigurableDashboard::run() runs the entire dashboard
     * application. This needs to be called in the main thread, and is blocking. Updating of widgets is handled on a periodic basis based
     * by the update rated specified in the constructor. There is an option to dynamically scale down the update rate based on program performance.
     * It is advisable to enable this option by setting QCD::QConfigurableDashboard::setAutoScale() to true because some features like file dialogs become
     * unusably slow when the cpu is saturated. Widgets can be told they are not visible (increasing performance) when the application
     * is not the active window on the computer by setting QCD::QConfigurableDashboard::setUpdateAlways() to false. A standard main function for a application
     * could be as follows:
     * ~~~ {.cpp}
     * int main(int argc, char **argv) {
     *  QCD::QConfigurableDashboard dashboard(argc, argv, 90);      // 90 Hz update rate
     *  dashboard.setUpdateAlways(true);
     *  dashboard.setAutoScale(false);
     *
     *  dashboard.addMenu("SettingsSubMenu", "Settings");           // Add sub menu to settings menu
     *  dashboard.addMenuAction("Action", "SettingsSubMenu");       // Add action to the new sub menu
     *
     *  YourModule module();                                        // This module could create the widgets for the application
     *  dashboard.addModule(&module);
     *
     *  DataModule dataModule();                                    // This module could populate data
     *  dashboard.addModule(&dataModule);
     *
     *  return dashboard.run();                                     // Blocking, runs the application
     * }
     * ~~~
     * @see QCD::Module Base class for all modules that can be used in a QConfigurableDashboard application
     * @see QCD::Widget Base class for all widgets that can be used in a QConfigurableDashboard application
     * @authors Patrick-McGuire
     */
    class QConfigurableDashboard : QObject {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_argc argc from main function
         * @param a_argv argc from main function
         * @param a_rate Update rate of the application in Hz
         */
        QConfigurableDashboard(int a_argc, char **a_argv, double a_rate = 30);

        /**
         * @brief Destructor
         */
        ~QConfigurableDashboard() override;

        /**
         * @brief Runs the application
         * @details Starts all modules and widgets, then enters the Qt main loop
         * @return exit code
         */
        int run();

        /**
         * @brief Sets the central widget of the application
         * @details Call this to set the core widget of the GUI. Usually this will be a container that you will add
         * many other widgets too.
         * @param a_widget QCD::Widget to add
         * @param a_alignment How to align the widget (see Qt alignment flags in the Qt docs)
         * @return if added successfully
         */
        bool setCentralWidget(Widget *a_widget, QFlags<Qt::AlignmentFlag> a_alignment = Qt::Alignment());

        /**
         * @brief Adds a module to the application
         * @details This registers the module internally, and sets the QCD::AppManager object in the module
         * @param a_baseModule QCD::Module to add
         * @return if added successfully
         */
        bool addModule(Module *a_baseModule);

        /**
         * @brief Adds a menu to the application
         * @details Adds a menu. Leave parent name blank or "none" to add to the root menu bar. There are a few stock menus that already exist, so don't try and add them (but
         * feel free to add to them): Settings, Tools and Theme.
         * @param a_name Name of menu to add
         * @pre must be unique
         * @param a_parentName Name of parent to add menu too
         * @pre must be a menu that has already been added
         * @return QMenu added
         */
        QMenu *addMenu(const QString &a_name, const QString &a_parentName = "none");

        /**
         * @brief Adds a action item to a menu
         * @details Adds a action. Leave parent name blank or "none" to add to the root menu bar.
         * @param a_name Name of action to add
         * @param a_parentName Name of parent to add menu too
         * @pre must be a menu that has already been added
         * @return QAction added
         */
        QAction *addMenuAction(const QString &a_name, const QString &a_parentName = "none");

        /**
         * @brief Sets the current theme
         * @details Sets the current theme. The name should be the key of the theme in the QCD::AppManager theme json object.
         * @param a_activeTheme name of theme
         */
        void updateTheme(const QString &a_activeTheme);

        /**
         * @brief Sets if the application checks whether it is the active application on the computer
         * @details Widgets can be told they are not visible (increasing performance) when the application
         * is not the active window on the computer by setting this to false
         * @param a_updateAlways if disabled
         */
        void setUpdateAlways(bool a_updateAlways);

        /**
         * @brief Sets if the application preforms autoscaling on it's update rate
         * @details Dynamically scale down the update rate based on program performance.
         * @param a_autoScale if enabled
         */
        void setAutoScale(bool a_autoScale);

        /**
         * @brief Get the AppManager object
         * @return QCD::AppManager object
         */
        AppManager *getAppManager();

    public slots:
        /**
         * @brief Slot for updating theme
         * @details Runs when user selects a new theme
         * @param a_action Action data
         */
        void updateTheme(QAction *a_action);

    private slots:
        void updateDragging(QAction *a_action);

        void updateGUI();

    private:
        static QString getClassStylesheet(const QString &a_class, const QString &a_style);

        QString getThemeData(const QString &a_themeName, const QString &a_attribute);

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
        Widget *m_centralWidget;
        std::vector<Module *> m_modules;
        boost::circular_buffer<double> m_times = boost::circular_buffer<double>(100);
    };

}


#endif //ROBOT_GUI_V3_QCONFIGURABLEDASHBOARD_H
