//
// Created by james on 12/11/15.
//

#include "bond-angle-dipole.h"

#include <cmath>

double BondAngleDipole::calcTorques(const MyTypes::vecList &x, const MyTypes::vecList &xr,
                                    MyTypes::vecList &fr) const{
    MyTypes::vec del = x[atoms_[1]] - x[atoms_[2]];
    if(box_ > 0.) del %= box_;

    const double r = vecabs(del);

    const double cosgamma = dot(xr[atoms_[0]], del) / (r * vecabs(xr[atoms_[0]]));
    const double dgamma = cosgamma - std::cos(equilibrium_);
    const double kdg = forceConstant_ * dgamma;

    MyTypes::vec torque = cross(del, xr[atoms_[0]]);
    torque *= 2. * kdg / vecabs(torque);

    fr[atoms_[0]] += torque;

    return kdg * dgamma;
}
