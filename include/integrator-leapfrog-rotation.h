//
// Created by james on 12/11/15.
//

#ifndef MINIMD_INTEGRATOR_LEAPFROG_ROTATION_H
#define MINIMD_INTEGRATOR_LEAPFROG_ROTATION_H

#include "integrator.h"

class IntegratorLeapfrogRotation : public Integrator{
public:
    IntegratorLeapfrogRotation(const int natoms, const double delt,
                       const MyEnums::IntegratorType type=MyEnums::IntegratorType::ROTATIONAL)
            : Integrator(natoms, delt, type){}
    double integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                     MyTypes::vecList &v, const MyTypes::vecList &f) const;
};

#endif //MINIMD_INTEGRATOR_LEAPFROG_ROTATION_H
