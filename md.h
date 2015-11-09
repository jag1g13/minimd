//
// Created by james on 17/08/15.
//

#ifndef MINIMD_MD_H
#define MINIMD_MD_H

#include <vector>
#include <array>
#include <memory>

#include "globals.h"
#include "integrator.h"
#include "bond-length.h"

class MD{
private:
    MyTypes::vecList x_;
    MyTypes::vecList xm_;
    MyTypes::vecList v_;
    MyTypes::vecList f_;
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

    std::vector<std::unique_ptr<Integrator>> integrators;
    std::vector<std::unique_ptr<BondLength>> bondLengths_;

    void bonded();
    void lj();

public:
    MD(){};
    ~MD(){};

    void createAtoms(const int natoms, const double temp);

    void calcForces();

    void setupBonded();

    void integrate();

    double temp() const;

    void print() const;
    double distSqr(const int i, const int j) const;
};

#endif //MINIMD_MD_H
