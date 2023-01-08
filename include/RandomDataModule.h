#ifndef QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H
#define QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H

#include "TimerModule.h"

namespace QCD {
    /**
     * @class RandomDataModule
     * @brief Populates the incoming data structure with random numbers and strings
     * @details Populates KEY1 through KEY6 where 1&2 are ints, 3&4 are doubles, and 5&6 are strings
     */
    class RandomDataModule : public TimerModule {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate Update rate
         */
        explicit RandomDataModule(double a_rate);

    private:
        /**
         * @brief Populates the data
         * @details Populates KEY1 through KEY6 where 1&2 are ints, 3&4 are doubles, and 5&6 are strings
         */
        void onUpdate() override;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_RANDOMDATAMODULE_H
