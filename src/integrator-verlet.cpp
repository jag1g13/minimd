//
// Created by james on 09/11/15.
//

#include "integrator-verlet.h"

double IntegratorVerlet::integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                                   MyTypes::vecList &v, const MyTypes::vecList &f) const{
    for(int i=0; i<natoms_; i++){
        xm[i] = (x[i] * 2) - xm[i] + f[i] * (delt_*delt_);
        v[i] = (xm[i] - x[i]) / delt_;
    }
    std::swap(x, xm);
}
