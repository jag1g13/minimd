//
// Created by james on 17/08/15.
//

#include "md.h"

#include <cmath>
#include <random>

#include "bond-length-harmonic.h"

#include "nonbond-lj.h"

#include "integrator-leapfrog.h"
#include "integrator-verlet.h"

#include "thermostat-vrescale.h"

#include "XTCOutput.h"
#include "LammpsTrjOutput.h"

void MD::createAtoms(const int natoms, const double temp){
    natoms_ = natoms;
    temp_ = temp;

    x_.resize(natoms_);
    xm_.resize(natoms_);
    v_.resize(natoms_);
    f_.resize(natoms_);

    xr_.resize(natoms_);
    xmr_.resize(natoms_);
    vr_.resize(natoms_);
    fr_.resize(natoms_);

//    std::random_device rd;
//    std::default_random_engine dre(rd());
    std::default_random_engine dre(0);
    std::uniform_real_distribution<double> rand(0, 1);

    for(int i=0; i < natoms_; i++){
        x_[i] = {rand(dre), rand(dre), rand(dre)};
        x_[i] *= box_;
    }

    if(temp != 0.){
        createVelocity(temp);
    }else{
        for(int i=0; i < natoms_; i++){
            v_[i] = {0., 0., 0.};
        }
    }

    for(int i=0; i < natoms_; i++){
        xm_[i] = x_[i] - (v_[i] * delt_);
    }
}

void MD::createVelocity(const double temp){
    std::default_random_engine dre(0);
    std::uniform_real_distribution<double> rand(0, 1);

    vec3d sumv = {0., 0., 0.}, sumv2 = {0., 0., 0.};
    for(int i=0; i < natoms_; i++){
        v_[i] = {rand(dre), rand(dre), rand(dre)};
        v_[i] -= 0.5;

        sumv += v_[i];
        sumv2 += v_[i] * v_[i];
    }

    sumv /= natoms_;
    sumv2 /= natoms_;

    const double scale = std::sqrt(3*temp_ / abs(sumv2));

    for(int i=0; i < natoms_; i++){
        v_[i] = (v_[i] - sumv) * scale;
    }
}

void MD::step(){
    energy_ = 0.;
    for(MyTypes::vec &each : f_) each = {0., 0., 0.};

    // Calculate forces
    for(const std::unique_ptr<Nonbond> &nonbond : nonbonds_)
        energy_ += nonbond->calcForces(x_, f_);
    for(const std::unique_ptr<BondLength> &bond : bondLengths_)
        energy_ += bond->calcForces(x_, f_);

    // Integrate forces
    for(const std::unique_ptr<Integrator> &intg : integrators_){
        switch(intg->type_){
            case MyEnums::IntegratorType::CARTESIAN:
                energy_ += intg->integrate(x_, xm_, v_, f_);
            case MyEnums::IntegratorType::ROTATIONAL:
                energy_ += intg->integrate(xr_, xmr_, vr_, fr_);
        }
    }

    // Do thermo/baro-stats
    for(const std::unique_ptr<Thermostat> &thermo : thermostats_)
        thermo->thermo(v_);

    // Correct for PBC
    for(int i=0; i<natoms_; i++) x_[i] -= std::floor(x_[i] / box_) * box_;

    step_++;
}

void MD::setup(){
//    bondLengths_.push_back(make_unique<BondLengthHarmonic>(0, 1, 1, 10));

    nonbonds_.push_back(make_unique<NonbondLJ>(natoms_, box_, 3));

//    integrators_.push_back(make_unique<IntegratorVerlet>(natoms_, delt_));
    integrators_.push_back(make_unique<IntegratorLeapfrog>(natoms_, delt_));
    integrators_.push_back(make_unique<IntegratorLeapfrog>(
            natoms_, delt_, MyEnums::IntegratorType::ROTATIONAL));

    thermostats_.push_back(make_unique<ThermostatVrescale>(1, 1));

    trjOutputs_.push_back(make_unique<XTCOutput>(natoms_, "out.xtc"));
    trjOutputs_.push_back(make_unique<LammpsTrjOutput>(natoms_, "out.trj"));
    trjOutputs_[1]->writeFrame(x_, step_, box_);
}

void MD::print(int natoms) const{
    if(natoms < 0) natoms = natoms_;

    for(int i=0; i<natoms; i++){
        printf("%1d %8.3f %8.3f %8.3f\n",
               i, x_[i].x, x_[i].y, x_[i].z);
    }
}

void MD::output() const{
//    for(const std::unique_ptr<TrjOutput> &trj : trjOutputs_) trj->writeFrame(x_, step_, box_);
    trjOutputs_[0]->writeFrame(x_, step_, box_);
}