#ifndef QCONFIGURABLEDASHBOARD_MODULE_H
#define QCONFIGURABLEDASHBOARD_MODULE_H

#include <QObject>
#include <CoreObject.h>

namespace QCD {
    class QConfigurableDashboard;       // Forward decl

    /**
     * @brief Base class for all modules
     * @details This class provides a interface for populating data, and adding widgets to the application.
     * You can set the central widget of the application through m_app. Data can be passed to the widgets in the runUpdate function though
     * the members defined in QCD::CoreObject. There are 2 other stock modules that are derived from QCD::Module, see below.
     * These provide more flexibility as to when you can runUpdate data.
     * @see QCD::ThreadedModule Runs in it's own thread
     * @see QCD::TimerModule Allows for a custom runUpdate rate
     */
    class Module : public QObject, public CoreObject {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @pre A QCD::ConfigurableDashboard object must be constructed previously
         */
        Module();
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_MODULE_H
