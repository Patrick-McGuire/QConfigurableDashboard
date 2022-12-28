#ifndef QCONFIGURABLEDASHBOARD_MODULE_H
#define QCONFIGURABLEDASHBOARD_MODULE_H

#include "QObject"
#include "AppManager.h"

namespace QCD {
    class QConfigurableDashboard;       // Forward decl

    /**
     * @brief Base class for all modules
     * @details This class provides a interface for populating data, and adding widgets to the application.
     * You can set the central widget of the application through the QCD::QConfigurableDashboard object,
     * which can be accessed from m_appManager. Data can be passed to the Widgets in the update function though
     * the QCD::AppManager instance. There are 2 other stock modules that are derived from QCD::Module, see below.
     * These provide more flexibility as to when you can update data.
     * @see QCD::ThreadedModule Runs in it's own thread
     * @see QCD::TimerModule Allows for a custom update rate
     */
    class Module : public QObject {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @pre A QCD::ConfigurableDashboard object must be constructed previously
         */
        Module();

        /**
         * @brief Setter for the QCD::AppManager member
         * @note This is handled internally, and should never be called outside of QCD's core classes.
         * @param a_appManager AppManager object to pass
         */
        static void setAppManager(AppManager *a_appManager);

        /**
         * @brief Get the AppManager object
         * @return QCD::AppManager object
         */
        static AppManager *getAppManager();

        /**
         * @brief Finish initializing this widget
         * @details This is called when QCD::QConfigurableDashboard::run() is called, and this calls QCD::Widget::onRun().
         */
        virtual void run();

        /**
         * Updates this
         */
        virtual void update();

        virtual void finish();

    protected:
        static AppManager *m_appManager;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_MODULE_H
