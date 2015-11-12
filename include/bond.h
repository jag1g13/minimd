//
// Created by james on 09/11/15.
//

#ifndef MINIMD_BOND_H
#define MINIMD_BOND_H

#include "globals.h"

class Bond{
protected:
    const double equilibrium_, forceConstant_;
    const double box_;
    Bond(const double eqm, const double fc, const double box)
            : equilibrium_(eqm), forceConstant_(fc), box_(box){};
public:
    virtual double calcForces(MyTypes::vecList &x, MyTypes::vecList &f) const = 0;

//    Bond(const Bond &other) = delete;
//    Bond &operator=(const Bond &other) = delete;
};


#endif //MINIMD_BOND_H
