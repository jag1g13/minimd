//
// Created by james on 09/11/15.
//

#ifndef MINIMD_NONBOND_LJ_H
#define MINIMD_NONBOND_LJ_H

#include "nonbond.h"

class NonbondLJ : public Nonbond{
protected:
    const int natoms_ = 10;
    const double sigma_ = 1.;
    const double epsilon_ = 1.;
public:
    double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f);
};

#endif //MINIMD_NONBOND_LJ_H
