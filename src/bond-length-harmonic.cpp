//
// Created by james on 09/11/15.
//

#include "bond-length-harmonic.h"

#include <cmath>

double BondLengthHarmonic::calcForces(const MyTypes::vecList &x, MyTypes::vecList &f) const{
    MyTypes::vec del = x[atoms_[0]] - x[atoms_[1]];
    if(box_ > 0.) del %= box_;

    const double r = vecabs(del);
    const double dr = r - equilibrium_;
    const double rk = forceConstant_ * dr;

    double fbond;
    if(r > 0.){
        fbond = -2. * rk / r;
    }else{
        fbond = 0.;
    }

    f[atoms_[0]] += del * fbond;
    f[atoms_[1]] -= del * fbond;

    return rk * dr;
}