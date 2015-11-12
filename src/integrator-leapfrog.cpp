//
// Created by james on 08/11/15.
//

#include "integrator-leapfrog.h"

double IntegratorLeapfrog::integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                                     MyTypes::vecList &v, const MyTypes::vecList &f) const{
    MyTypes::vec sumv  = {0., 0., 0.};
    MyTypes::vec sumv2 = {0., 0., 0.};

    for(int i=0; i<natoms_; i++){
        v[i] += f[i] * delt_;
        xm[i] = x[i] + (v[i] * delt_);
        sumv += v[i];
        sumv2 += v[i] * v[i];
    }
    std::swap(x, xm);
    return -0.5 * vecabs(sumv2);
}