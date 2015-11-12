//
// Created by james on 12/11/15.
//

#include "integrator-leapfrog-rotation.h"

double IntegratorLeapfrogRotation::integrate(MyTypes::vecList &x, MyTypes::vecList &xm,
                                     MyTypes::vecList &v, const MyTypes::vecList &f) const{
    MyTypes::vec sumv  = {0., 0., 0.};
    MyTypes::vec sumv2 = {0., 0., 0.};

    for(int i=0; i<natoms_; i++){
        v[i] += f[i] * delt_;
        xm[i] = x[i] + (cross(v[i], x[i]) * delt_);
        xm[i] /= vecabs(xm[i]);
        sumv += v[i];
        sumv2 += v[i] * v[i];
    }
    std::swap(x, xm);
    return 0.5 * vecabs(sumv2);
}