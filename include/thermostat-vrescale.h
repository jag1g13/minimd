//
// Created by james on 10/11/15.
//

#ifndef MINIMD_THERMOSTAT_VRESCALE_H
#define MINIMD_THERMOSTAT_VRESCALE_H

#include "thermostat.h"

class ThermostatVrescale : public Thermostat{
protected:
public:
    ThermostatVrescale(const double temp, const double coup=1.) : Thermostat(temp, coup){};

    double thermo(MyTypes::vecList &v);

    double thermo(MyTypes::vecList &v, MyTypes::vecList &vr);
};

#endif //MINIMD_THERMOSTAT_VRESCALE_H
