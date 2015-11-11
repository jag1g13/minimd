//
// Created by james on 08/11/15.
//

#ifndef MINIMD_INTEGRATOR_H
#define MINIMD_INTEGRATOR_H

#include "globals.h"

class Integrator{
protected:
    const int natoms_;
    const double delt_;

    Integrator(const int natoms, const double delt, const MyEnums::IntegratorType type)
            : natoms_(natoms), delt_(delt), type_(type){}
public:
    const MyEnums::IntegratorType type_;

    virtual double integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                             MyTypes::vecList &v, const MyTypes::vecList &f) const = 0;
};

#endif //MINIMD_INTEGRATOR_H
