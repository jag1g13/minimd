//
// Created by james on 17/08/15.
//

#include "md.h"

#include <cmath>
#include <random>
#include <iostream>

void MD::createAtoms(const int natoms, const double temp,
                     const double bounda, const double boundb){
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
        x_[i] *= (boundb - bounda);
        x_[i] += bounda;
        xr_[i] = {1., 0., 0.};
    }

    if(temp != 0.){
        createVelocity(temp);
        for(int i=0; i < natoms_; i++) xm_[i] = x_[i] - (v_[i] * delt_);
    }else{
        for(int i=0; i < natoms_; i++){
            v_[i] = {0., 0., 0.};
            xm_[i] = x_[i];
        }
    }

    if(trjOutputs_.size() > 1) trjOutputs_[1]->writeFrame(x_, xr_, 0, abs(box_));
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

    const double scale = std::sqrt(3*temp_ / vecabs(sumv2));

    for(int i=0; i < natoms_; i++){
        v_[i] = (v_[i] - sumv) * scale;
    }
}

void MD::step(){
    energy_ = 0.; pe_ = 0.; ke_ = 0.; cartke_ = 0.; rotke_ = 0.;
    for(MyTypes::vec &each : f_) each = {0., 0., 0.};
    for(MyTypes::vec &each : fr_) each = {0., 0., 0.};

    // Calculate forces
    for(const std::unique_ptr<Nonbond> &nonbond : nonbonds_)
        pe_ += nonbond->calcForces(x_, f_);
    for(const std::unique_ptr<BondLength> &bond : bondLengths_)
        pe_ += bond->calcForces(x_, f_);

    //TODO make this work with normal angles too
    for(const std::unique_ptr<BondAngle> &bond : bondAngles_)
        pe_ += bond->calcTorques(x_, xr_, fr_);

    // Integrate forces
    for(const std::unique_ptr<Integrator> &intg : integrators_){
        switch(intg->type_){
            case MyEnums::IntegratorType::CARTESIAN:
                cartke_ += intg->integrate(x_, xm_, v_, f_);
                break;
            case MyEnums::IntegratorType::ROTATIONAL:
                rotke_ += intg->integrate(xr_, xmr_, vr_, fr_);
                break;
        }
    }
    ke_ = cartke_ + rotke_;

    // Do thermo/baro-stats
    for(const std::unique_ptr<Thermostat> &thermo : thermostats_)
        thermo->thermo(v_);

    // Correct for PBC
    if(box_ > 0.) pbc();

    energy_ = pe_ + ke_;
    step_++;
}

void MD::pbc(){
    for(int i = 0; i < natoms_; i++){
        while(x_[i].x < 0){
            x_[i].x += box_;
            xm_[i].x += box_;
        }
        while(x_[i].x >= box_){
            x_[i].x -= box_;
            xm_[i].x -= box_;
        }

        while(x_[i].y < 0){
            x_[i].y += box_;
            xm_[i].y += box_;
        }
        while(x_[i].y >= box_){
            x_[i].y -= box_;
            xm_[i].y -= box_;
        }

        while(x_[i].z < 0){
            x_[i].z += box_;
            xm_[i].z += box_;
        }
        while(x_[i].z >= box_){
            x_[i].z -= box_;
            xm_[i].z -= box_;
        }
    }
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
    trjOutputs_[0]->writeFrame(x_, step_, abs(box_));
    trjOutputs_[1]->writeFrame(x_, xr_, step_, abs(box_));
}