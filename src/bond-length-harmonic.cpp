//
// Created by james on 09/11/15.
//

#include "bond-length-harmonic.h"

#include <cmath>

void BondLengthHarmonic::calcForces(MyTypes::vecList &x, MyTypes::vecList &f) const{
    MyTypes::vec del = x[atoms_[0]] - x[atoms_[1]];
//    del[0] = x[atoms_[0]][0] - x[atoms_[1]][0];
//    del[1] = x[atoms_[0]][1] - x[atoms_[1]][1];
//    del[2] = x[atoms_[0]][2] - x[atoms_[1]][2];

    const double r = abs(del);
//    const double r = std::sqrt(del[0]*del[0] + del[1]*del[1] + del[2]*del[2]);
    const double dr = r - equilibrium_;
    const double rk = forceConstant_ * dr;

    double fbond;
    if(r > 0.){
        fbond = -2. * rk / r;
    }else{
        fbond = 0.;
    }

    f[atoms_[0]] += del * fbond;
//    f[atoms_[0]][0] += del[0] * fbond;
//    f[atoms_[0]][1] += del[1] * fbond;
//    f[atoms_[0]][2] += del[2] * fbond;
    f[atoms_[1]] -= del * fbond;
//    f[atoms_[1]][0] -= del[0] * fbond;
//    f[atoms_[1]][1] -= del[1] * fbond;
//    f[atoms_[1]][2] -= del[2] * fbond;
}