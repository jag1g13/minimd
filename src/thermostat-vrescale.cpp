//
// Created by james on 10/11/15.
//

#include "thermostat-vrescale.h"

#include <cmath>

double ThermostatVrescale::thermo(MyTypes::vecList &v){
    const double temp = temperature(v);
    const double scale = std::sqrt(refTemp_ / temp);

    for(MyTypes::vec &velo : v) velo *= scale;
}