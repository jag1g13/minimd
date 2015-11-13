//
// Created by james on 13/11/15.
//

#ifndef MINIMD_NONBOND_CARTESIAN_H
#define MINIMD_NONBOND_CARTESIAN_H

#include "nonbond.h"

class NonbondCartesian : public Nonbond{
protected:
public:
    NonbondCartesian(const int natoms, const double box, const double cut=-1.)
            : Nonbond(natoms, box, cut){};

    virtual double calcForces(const MyTypes::vecList &x, const MyTypes::vecList &xr,
                              MyTypes::vecList &f, MyTypes::vecList &fr){
        throw std::runtime_error("Function not implemented: NonbondCartesian::calcForces");
    };
};

#endif //MINIMD_NONBOND_CARTESIAN_H
