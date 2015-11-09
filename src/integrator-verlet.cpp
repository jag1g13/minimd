//
// Created by james on 09/11/15.
//

#include "integrator-verlet.h"

void IntegratorVerlet::integrate(const int natoms, const double delt,
                                   MyTypes::vecList &x, MyTypes::vecList &xm,
                                   MyTypes::vecList &v, const MyTypes::vecList &f) const{
    for(int i=0; i<natoms; i++){
        xm[i][0] = 2*x[i][0] - xm[i][0] + delt*delt*f[i][0];
        xm[i][1] = 2*x[i][1] - xm[i][1] + delt*delt*f[i][1];
        xm[i][2] = 2*x[i][2] - xm[i][2] + delt*delt*f[i][2];
        v[i][0] = (xm[i][0] - x[i][0]) / delt;
        v[i][1] = (xm[i][1] - x[i][1]) / delt;
        v[i][2] = (xm[i][2] - x[i][2]) / delt;
    }
    std::swap(x, xm);
}
