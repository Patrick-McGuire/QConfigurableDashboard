#ifndef QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H
#define QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H

#include "ThreadedModule.h"

namespace QCD {
    /**
     * @class TRandomDataModule
     * @brief Populates the incoming data structure with random numbers and strings
     * @details Populates KEY1 through KEY6 where 1&2 are ints, 3&4 are doubles, and 5&6 are strings
     * KEY7 and KEY8 are sin/cos functions
     */
    class TRandomDataModule : public ThreadedModule {
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param a_rate Update rate
         */
        explicit TRandomDataModule(double a_rate);

    private:
        /**
         * @brief Populates the data
         * @details Populates KEY1 through KEY6 where 1&2 are ints, 3&4 are doubles, and 5&6 are strings
         * KEY7 and KEY8 are sin/cos functions
         */
        void tick() override;

        double m_x = 0;
    };

} // QCD

#endif //QCONFIGURABLEDASHBOARD_TRANDOMDATAMODULE_H
