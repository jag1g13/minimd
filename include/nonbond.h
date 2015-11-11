//
// Created by james on 09/11/15.
//

#ifndef MINIMD_NONBOND_H
#define MINIMD_NONBOND_H

#include "globals.h"

class Nonbond{
protected:
    const int natoms_;
    const double box_;

    Nonbond(const int natoms, const double box) : natoms_(natoms), box_(box){};

    double distSqr(const MyTypes::vec &a, const MyTypes::vec &b) const{
        MyTypes::vec del = a - b;
        del %= box_;
        return abs(del);
    };

public:
    virtual double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f) = 0;
};

#endif //MINIMD_NONBOND_H
