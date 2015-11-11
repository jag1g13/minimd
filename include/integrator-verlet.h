//
// Created by james on 09/11/15.
//

#ifndef MINIMD_INTEGRATOR_VERLET_H
#define MINIMD_INTEGRATOR_VERLET_H

#include "integrator.h"

class IntegratorVerlet : public Integrator{
public:
    IntegratorVerlet(const int natoms, const double delt)
            : Integrator(natoms, delt, MyEnums::IntegratorType::CARTESIAN){}
    double integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                     MyTypes::vecList &v, const MyTypes::vecList &f) const;
};

#endif //MINIMD_INTEGRATOR_VERLET_H
