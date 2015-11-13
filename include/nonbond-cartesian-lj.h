//
// Created by james on 09/11/15.
//

#ifndef MINIMD_NONBOND_CARTESIAN_LJ_H
#define MINIMD_NONBOND_CARTESIAN_LJ_H

#include "nonbond-cartesian.h"

class NonbondCartesianLJ : public NonbondCartesian{
protected:
    const double sigma_ = 1.;
    const double epsilon_ = 1.;

public:
    NonbondCartesianLJ(const int natoms, const double box, const double cut=-1.)
            : NonbondCartesian(natoms, box, cut){};

    double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f);
};

#endif //MINIMD_NONBOND_CARTESIAN_LJ_H
