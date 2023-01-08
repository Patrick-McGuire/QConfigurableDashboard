#ifndef QCONFIGURABLEDASHBOARD_TIMERMODULE_H
#define QCONFIGURABLEDASHBOARD_TIMERMODULE_H

#include "Module.h"
#include "QTimer"

namespace QCD {
    /**
     * @class TimerModule
     * @brief Base Module that allows for a custom update rate
     * @details Using a QTimer (meaning update rate may vary significantly if running at high rates
     */
    class TimerModule : public Module {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate rate to run timer at (Hz)
         */
        explicit TimerModule(double a_rate);

        /**
         * @brief Starts the updates
         * @details Should only be called internal to QCD
         * @return 0
         */
        int run() override;

    protected slots:
        /**
         * @brief Called at specified rate
         * @details Pure virtual function, this is where you put your primary code.
         * DO NOT put blocking code in here (use QCD::ThreadedModule for blocking code), blocking code
         * will hang the main thread, preventing everything from working (yes, everything).
         */
        virtual void onUpdate();

    protected:
        int m_interval;             ///< Time (ms) between updates
        QTimer *m_timer;            ///< QT timer object

    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TIMERMODULE_H
