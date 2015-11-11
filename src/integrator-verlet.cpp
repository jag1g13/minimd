//
// Created by james on 09/11/15.
//

#include "integrator-verlet.h"

double IntegratorVerlet::integrate(const int natoms, const double delt,
                                   MyTypes::vecList &x, MyTypes::vecList &xm,
                                   MyTypes::vecList &v, const MyTypes::vecList &f) const{
    for(int i=0; i<natoms; i++){
        xm[i] = (x[i] * 2) - xm[i] + f[i] * (delt*delt);
        v[i] = (xm[i] - x[i]) / delt;
    }
    std::swap(x, xm);
}
