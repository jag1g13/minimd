//
// Created by james on 12/11/15.
//

#ifndef MINIMD_BOND_ANGLE_H
#define MINIMD_BOND_ANGLE_H

#include "bond.h"

class BondAngle : public Bond{
protected:
    const int atoms_[3];
    BondAngle(const int a, const int b, const int c,
              const double eqm, const double fc, const double box)
            : Bond(eqm, fc, box), atoms_{a, b, c} {};
public:
};

#endif //MINIMD_BOND_ANGLE_H
