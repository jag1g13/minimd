//
// Created by james on 08/11/15.
//

#ifndef MINIMD_INTEGRATOR_LEAPFROG_H
#define MINIMD_INTEGRATOR_LEAPFROG_H

#include "integrator.h"

class IntegratorLeapfrog : public Integrator{
public:
    IntegratorLeapfrog(const int natoms, const double delt,
                       const MyEnums::IntegratorType type=MyEnums::IntegratorType::CARTESIAN)
            : Integrator(natoms, delt, type){}
    double integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                     MyTypes::vecList &v, const MyTypes::vecList &f) const;
};

#endif //MINIMD_INTEGRATOR_LEAPFROG_H
