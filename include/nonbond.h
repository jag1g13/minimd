//
// Created by james on 09/11/15.
//

#ifndef MINIMD_NONBOND_H
#define MINIMD_NONBOND_H

#include "globals.h"

class Nonbond{
protected:
    Nonbond(){};
    double distSqr(const MyTypes::vec &a, const MyTypes::vec &b) const{
        double d[3];
        d[0] = a[0] - b[0];
        d[1] = a[1] - b[1];
        d[2] = a[2] - b[2];
        return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
    };
public:
    virtual double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f) = 0;
};

#endif //MINIMD_NONBOND_H
