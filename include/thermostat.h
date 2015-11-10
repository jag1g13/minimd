//
// Created by james on 10/11/15.
//

#ifndef MINIMD_THERMOSTAT_H
#define MINIMD_THERMOSTAT_H

#include "globals.h"

class Thermostat{
protected:
    const double refTemp_;
    const double coupling_;

    Thermostat(const double temp, const double coup) : refTemp_(temp), coupling_(coup){};

public:
    double temperature(const MyTypes::vecList &v) const{
        MyTypes::vec sumv2 = {0., 0., 0.};
        for(const MyTypes::vec &velo : v) sumv2 += velo * velo;
        return abs(sumv2) / (3 * v.size());
    }

    virtual double thermo(MyTypes::vecList &v) = 0;
};

#endif //MINIMD_THERMOSTAT_H
