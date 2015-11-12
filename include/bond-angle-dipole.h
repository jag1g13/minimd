//
// Created by james on 12/11/15.
//

#ifndef MINIMD_BOND_ANGLE_DIPOLE_H
#define MINIMD_BOND_ANGLE_DIPOLE_H

#include "bond-angle.h"

class BondAngleDipole : public BondAngle{
protected:
public:
    BondAngleDipole(const int a, const int b, const int c,
              const double eqm, const double fc, const double box)
            : BondAngle(a, b, c, eqm, fc, box){};

    double calcTorques(const MyTypes::vecList &x, const MyTypes::vecList &xr,
                       MyTypes::vecList &fr) const;
};

#endif //MINIMD_BOND_ANGLE_DIPOLE_H
