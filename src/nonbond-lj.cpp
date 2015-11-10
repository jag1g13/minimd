//
// Created by james on 09/11/15.
//

#include "nonbond-lj.h"

#include <cmath>

double NonbondLJ::calcForces(const MyTypes::vecList &x, MyTypes::vecList &f){
//    double cut2i = 1. / (cutoff_*cutoff_);
//    double cut6i = cut2i*cut2i*cut2i;
//    ecut_ = 4 * cut6i * (cut6i - 1);

    for(int i = 0; i < natoms_; i++){
        f[i] = {0., 0., 0.};
//        f[i][0] = 0.;
//        f[i][1] = 0.;
//        f[i][2] = 0.;
    }

    for(int i = 0; i < natoms_; i++){
        for(int j = i + 1; j < natoms_; j++){
            double r2 = distSqr(x[i], x[j]);
            double r2i = 1. / r2;
            double r6i = r2i * r2i * r2i * std::pow(sigma_, 6);
            double ff = 48 * epsilon_ * r2i * r6i * (r6i - 0.5);
            f[i] += (x[i] - x[j]) * ff;
//            f[i][0] += ff * (x[i][0] - x[j][0]);
//            f[i][1] += ff * (x[i][1] - x[j][1]);
//            f[i][2] += ff * (x[i][2] - x[j][2]);
            f[j] -= (x[i] - x[j]) * ff;
//            f[j][0] -= ff * (x[i][0] - x[j][0]);
//            f[j][1] -= ff * (x[i][1] - x[j][1]);
//            f[j][2] -= ff * (x[i][2] - x[j][2]);
        }
    }

    return -1.;
}
