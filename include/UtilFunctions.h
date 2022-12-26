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

    inline double getEpochTime() {
        return (double) std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch()).count() / 1000;
    }

    inline Json qVariantToJson(QVariant &a_variant) {
        if(a_variant.type() == QVariant::String) {
            return a_variant.toString().toStdString();
        } else if(a_variant.type() == QVariant::Int) {
            return a_variant.toInt();
        } else if(a_variant.type() == QVariant::Double) {
            return a_variant.toDouble();
        } else if(a_variant.type() == QVariant::Map) {
            Json output;
            auto map = a_variant.toMap();
            auto mapKeys = map.keys();
            for(auto &el : mapKeys) {
                output[el.toStdString()] = qVariantToJson(map[el]);
            }
        } else if(a_variant.type() == QVariant::List) {
            Json output = Json::array();
            auto map = a_variant.toList();
            for(auto &el : map) {
                output.push_back(qVariantToJson(el));
            }
        }
        return {};
    }
}

#endif //QCONFIGURABLEDASHBOARD_UTILFUNTIONS_H
