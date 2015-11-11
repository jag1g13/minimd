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
#include "thermostat.h"

#include "bond-length.h"
#include "nonbond.h"

#include "trj_output.h"

class MD{
private:
    MyTypes::vecList x_;
    MyTypes::vecList xm_;
    MyTypes::vecList v_;
    MyTypes::vecList f_;

    MyTypes::vecList xr_;
    MyTypes::vecList xmr_;
    MyTypes::vecList vr_;
    MyTypes::vecList fr_;

    double box_ = 10;
    int natoms_, step_ = 0;
    double temp_= 300.;
    double delt_ = 0.01;

    double mass_ = 1.;

    double energy_;

    std::vector<std::unique_ptr<Integrator>> integrators_;
    std::vector<std::unique_ptr<Thermostat>> thermostats_;

    std::vector<std::unique_ptr<BondLength>> bondLengths_;
    std::vector<std::unique_ptr<Nonbond>> nonbonds_;

    std::vector<std::unique_ptr<TrjOutput>> trjOutputs_;

    void createVelocity(const double temp);

public:
    MD(){};
    ~MD(){};

    void createAtoms(const int natoms, const double temp);

    void setup();

    void step();

    void output() const;

    void print(int natoms=-1) const;
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args){
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //MINIMD_MD_H
