//
// Created by james on 08/11/15.
//

#include "integrator-leapfrog.h"

double IntegratorLeapfrog::integrate(const int natoms, const double delt,
               MyTypes::vecList &x, MyTypes::vecList &xm,
               MyTypes::vecList &v, const MyTypes::vecList &f) const{
    MyTypes::vec sumv  = {0., 0., 0.};
    MyTypes::vec sumv2 = {0., 0., 0.};

    for(int i=0; i<natoms; i++){
        v[i] += f[i] * delt;
//        v[i][0] += f[i][0]*delt;
//        v[i][1] += f[i][1]*delt;
//        v[i][2] += f[i][2]*delt;
        xm[i] = x[i] + (v[i] * delt);
//        xm[i][0] = x[i][0] + v[i][0]*delt;
//        xm[i][1] = x[i][1] + v[i][1]*delt;
//        xm[i][2] = x[i][2] + v[i][2]*delt;
        sumv += v[i];
        sumv2 += v[i] * v[i];
    }
    std::swap(x, xm);
    return -0.5 * abs(sumv2);
}