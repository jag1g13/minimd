//
// Created by james on 09/11/15.
//

#include "nonbond-cartesian-lj.h"

#include <cmath>

double NonbondCartesianLJ::calcForces(const MyTypes::vecList &x, MyTypes::vecList &f){
    double en = 0.;
    const double sig6 = sigma_*sigma_*sigma_*sigma_*sigma_*sigma_;

    double ecut = 0.;
    if(cutoff_ < 0){
        const double cut2i = 1. / (cutoff_*cutoff_);
        const double cut6i = cut2i*cut2i*cut2i;
        ecut = 4 * cut6i * (cut6i - 1);
    }

#pragma omp parallel for default(none) shared(x, f, ecut) reduction(+:en) schedule(static, 1)
    for(int i = 0; i < natoms_; i++){
        for(int j = i + 1; j < natoms_; j++){
            double r2 = distSqr(x[i], x[j]);
            if(cutoff_ <= 0. || r2 <= cutoff_*cutoff_){
                double r2i = 1. / r2;
                double r6i = r2i * r2i * r2i * sig6;
                double ff = 48 * epsilon_ * r2i * r6i * (r6i - 0.5);
                MyTypes::vec del = x[i] - x[j];
                if(box_ > 0.) del %= box_;
                del *= ff;
                f[i] += del;
                f[j] -= del;
                en += 4 * r6i * (r6i - 1) - ecut;
            }
        }
    }

    return en;
}
