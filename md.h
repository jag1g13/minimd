//
// Created by james on 17/08/15.
//

#ifndef MINIMD_MD_H
#define MINIMD_MD_H

#include <vector>
#include <array>

#include "integrator.h"

class MD{
private:
    std::vector<std::array<double, 3>> x_;
    std::vector<std::array<double, 3>> xm_;
    std::vector<std::array<double, 3>> v_;
    std::vector<std::array<double, 3>> f_;
    double box_ = 5;
    int natoms_;
    double en_;
    double temp_= 300.;
    double delt_ = 0.01;

    double sigma_ = 1.;
    double epsilon_ = 1.;
    double mass_ = 1.;
    double cutoff_ = 10.;
    double ecut_;

    std::vector<Integrator> integrators;

public:
    MD(){};
    ~MD(){};

    void createAtoms(const int natoms, const double temp);

    void lj();

    void integrate();

    double temp() const;

    void print() const;
    double distSqr(const int i, const int j) const;
};

#endif //MINIMD_MD_H
