//
// Created by james on 13/11/15.
//

#ifndef MINIMD_NONBOND_ROTATION_DIPOLE_H
#define MINIMD_NONBOND_ROTATION_DIPOLE_H

#include "nonbond-rotation.h"

class NonbondRotationDipole : public NonbondRotation{
protected:
public:
    NonbondRotationDipole(const int natoms, const double box, const double cut=-1.)
            : NonbondRotation(natoms, box, cut){};

    double calcForces(const MyTypes::vecList &x, const MyTypes::vecList &xr,
                      MyTypes::vecList &f, MyTypes::vecList &fr);
};

#endif //MINIMD_NONBOND_ROTATION_DIPOLE_H
