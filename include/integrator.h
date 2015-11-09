//
// Created by james on 08/11/15.
//

#ifndef MINIMD_INTEGRATOR_H
#define MINIMD_INTEGRATOR_H

#include "globals.h"

class Integrator{
private:
public:
    virtual void integrate(const int natoms, const double delt,
                           MyTypes::vecList &x, MyTypes::vecList &xm,
                           MyTypes::vecList &v, const MyTypes::vecList &f) const = 0;
};

#endif //MINIMD_INTEGRATOR_H
