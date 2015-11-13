//
// Created by james on 13/11/15.
//

#ifndef MINIMD_NONBOND_ROTATION_H
#define MINIMD_NONBOND_ROTATION_H

#include "nonbond.h"

class NonbondRotation : public Nonbond{
protected:
public:
    NonbondRotation(const int natoms, const double box, const double cut=-1.)
            : Nonbond(natoms, box, cut){};

    virtual double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f){
        throw std::runtime_error("Function not implemented: NonbondRotation::calcForces");
    };
};

#endif //MINIMD_NONBOND_ROTATION_H
