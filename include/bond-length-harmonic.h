//
// Created by james on 09/11/15.
//

#ifndef MINIMD_BOND_HARMONIC_H
#define MINIMD_BOND_HARMONIC_H

#include "bond-length.h"

class BondLengthHarmonic : public BondLength{
private:
public:
    BondLengthHarmonic(const int a, const int b, const double eqm, const double fc, const double box)
                       : BondLength(a, b, eqm, fc, box){}

    double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f) const;
};

#endif //MINIMD_BOND_HARMONIC_H
