//
// Created by james on 09/11/15.
//

#ifndef MINIMD_BOND_LENGTH_H
#define MINIMD_BOND_LENGTH_H

#include "bond.h"

class BondLength : public Bond{
protected:
    const int atoms_[2];
    BondLength(const int a, const int b, const double eqm, const double fc, const double box)
               : Bond(eqm, fc, box), atoms_{a, b} {};
public:
};

#endif //MINIMD_BOND_LENGTH_H
