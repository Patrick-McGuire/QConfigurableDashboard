#include "cstdint"
#include "cstdlib"

#ifndef QCONFIGURABLEDASHBOARD_UTILFUNTIONS_H
#define QCONFIGURABLEDASHBOARD_UTILFUNTIONS_H

namespace QCD {
    inline int randomInt(int a_min, int a_max) {
        return rand() % (a_max - a_min + 1) + a_min;

    }

    inline double randomDouble(double a_min, double a_max) {
        return a_min + ((double) rand() / RAND_MAX) * (a_max - a_min);
    }

    inline std::string randomString(int len) {
        std::string output;
        output.reserve(len);
        for (int i = 0; i < len; i++) {
            output += (char) randomInt('A', 'z');
        }
        return output;
    }
}

#endif //QCONFIGURABLEDASHBOARD_UTILFUNTIONS_H
