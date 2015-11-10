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
        return abs(a - b);
//        double d[3];
//        d[0] = a.x - b.x;
//        d[1] = a.y - b.y;
//        d[2] = a.z - b.z;
//        return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
    };
public:
    virtual double calcForces(const MyTypes::vecList &x, MyTypes::vecList &f) = 0;
};

#endif //MINIMD_NONBOND_H
