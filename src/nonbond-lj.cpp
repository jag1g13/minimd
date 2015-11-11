//
// Created by james on 09/11/15.
//

#include "nonbond-lj.h"

#include <cmath>

double NonbondLJ::calcForces(const MyTypes::vecList &x, MyTypes::vecList &f){
//    double cut2i = 1. / (cutoff_*cutoff_);
//    double cut6i = cut2i*cut2i*cut2i;
//    ecut_ = 4 * cut6i * (cut6i - 1);
    double en = 0.;

    for(int i = 0; i < natoms_; i++){
        f[i] = {0., 0., 0.};
    }

    for(int i = 0; i < natoms_; i++){
        for(int j = i + 1; j < natoms_; j++){
            double r2 = distSqr(x[i], x[j]);
            double r2i = 1. / r2;
            double r6i = r2i * r2i * r2i * std::pow(sigma_, 6);
            double ff = 48 * epsilon_ * r2i * r6i * (r6i - 0.5);
            MyTypes::vec del = x[i] - x[j];
            del %= box_;
            f[i] += del * ff;
            f[j] -= del * ff;
            en += 4 * r6i * (r6i - 1);
        }
    }

    return en;
}
