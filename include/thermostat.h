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

    Thermostat(const double temp, const double coup=1.) : refTemp_(temp), coupling_(coup){};

public:
    double temperature(const MyTypes::vecList &v) const{
        MyTypes::vec sumv2 = {0., 0., 0.};
        for(const MyTypes::vec &velo : v) sumv2 += velo * velo;
        return vecabs(sumv2) / (3 * v.size());
    }

    virtual double thermo(MyTypes::vecList &v) = 0;

    virtual double thermo(MyTypes::vecList &v, MyTypes::vecList &vr){
        throw std::runtime_error("Function not implemented: thermo");
    }
};

#endif //MINIMD_THERMOSTAT_H
