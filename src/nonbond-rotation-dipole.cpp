//
// Created by james on 13/11/15.
//

#include "nonbond-rotation-dipole.h"

#include <cmath>

double NonbondRotationDipole::calcForces(const MyTypes::vecList &x, const MyTypes::vecList &xr,
                                         MyTypes::vecList &f, MyTypes::vecList &fr){
    double en = 0.;
    const double sig6 = 1;

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
                double ff = 48 * r2i * r6i * (r6i - 0.5);
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
