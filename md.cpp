//
// Created by james on 17/08/15.
//

#include "md.h"

#include <cmath>
#include <random>
#include <XTCOutput.h>

#include "bond-length-harmonic.h"

#include "nonbond-lj.h"

#include "integrator-leapfrog.h"
#include "integrator-verlet.h"

#include "thermostat-vrescale.h"

#include "XTCOutput.h"

void MD::createAtoms(const int natoms, const double temp){
    natoms_ = natoms;
    temp_ = temp;
    x_.resize(natoms_);
    xm_.resize(natoms_);
    v_.resize(natoms_);
    f_.resize(natoms_);

//    std::random_device rd;
//    std::default_random_engine dre(rd());
    std::default_random_engine dre(0);
    std::uniform_real_distribution<double> rand(0, 1);

    for(int i=0; i < natoms_; i++){
        x_[i] = {rand(dre), rand(dre), rand(dre)};
        x_[i] *= box_;
//                x_[i][1] = rand(dre) * box_;
//                x_[i][2] = rand(dre) * box_;
    }

    if(temp != 0.){
        createVelocity(temp);
    }else{
        for(int i=0; i < natoms_; i++){
            v_[i] = {0., 0., 0.};
//            v_[i][0] = 0.;
//            v_[i][1] = 0.;
//            v_[i][2] = 0.;
        }
    }

    for(int i=0; i < natoms_; i++){
        xm_[i] = x_[i] - (v_[i] * delt_);
//        xm_[i][0] = x_[i][0] - v_[i][0] * delt_;
//        xm_[i][1] = x_[i][1] - v_[i][1] * delt_;
//        xm_[i][2] = x_[i][2] - v_[i][2] * delt_;
    }
}

void MD::createVelocity(const double temp){
    std::default_random_engine dre(0);
    std::uniform_real_distribution<double> rand(0, 1);

    vec3d sumv = {0., 0., 0.}, sumv2 = {0., 0., 0.};
    for(int i=0; i < natoms_; i++){
        v_[i] = {rand(dre), rand(dre), rand(dre)};
        v_[i] -= 0.5;
//        v_[i][0] = rand(dre) - 0.5;
//        v_[i][1] = rand(dre) - 0.5;
//        v_[i][2] = rand(dre) - 0.5;

        sumv += v_[i];
//        sumv[0] += v_[i][0];
//        sumv[1] += v_[i][1];
//        sumv[2] += v_[i][2];
//        sumv2[0] += v_[i][0] * v_[i][0];
//        sumv2[1] += v_[i][1] * v_[i][1];
//        sumv2[2] += v_[i][2] * v_[i][2];
    }

    sumv /= natoms_;
//    sumv[0] /= natoms_;
//    sumv[1] /= natoms_;
//    sumv[2] /= natoms_;
    sumv2 /= natoms_;
//    sumv2[0] /= natoms_;
//    sumv2[1] /= natoms_;
//    sumv2[2] /= natoms_;

//    const double abssumv2 = std::sqrt(sumv2[0] + sumv2[1] + sumv2[2]);
    const double abssumv2 = std::sqrt(sumv2.x + sumv2.y + sumv2.z);
    const double scale = std::sqrt(3*temp_ / abssumv2);

    for(int i=0; i < natoms_; i++){
        v_[i] = (v_[i] - sumv) * scale;
//        v_[i][0] = (v_[i][0] - sumv[0]) * scale;
//        v_[i][1] = (v_[i][1] - sumv[1]) * scale;
//        v_[i][2] = (v_[i][2] - sumv[2]) * scale;

    }
}

void MD::calcForces(){
    energy_ = 0.;
//    bonded();
    for(const std::unique_ptr<Nonbond> &nonbond : nonbonds_)
        energy_ += nonbond->calcForces(x_, f_);
}

void MD::bonded(){
    for(const std::unique_ptr<BondLength> &bond : bondLengths_)
        energy_ += bond->calcForces(x_, f_);
}

void MD::setup(){
    bondLengths_.push_back(make_unique<BondLengthHarmonic>(0, 1, 1, 10));

    nonbonds_.push_back(make_unique<NonbondLJ>(natoms_, box_));

//    integrators_.push_back(make_unique<IntegratorVerlet>());
    integrators_.push_back(make_unique<IntegratorLeapfrog>());

    thermostats_.push_back(make_unique<ThermostatVrescale>(1, 1));

    trjOutputs_.push_back(make_unique<XTCOutput>(natoms_, "out.xtc"));
}

void MD::integrate(){
    for(const std::unique_ptr<Integrator> &intg : integrators_)
        energy_ += intg->integrate(natoms_, delt_, x_, xm_, v_, f_);
    for(const std::unique_ptr<Thermostat> &thermo : thermostats_)
        thermo->thermo(v_);
    step_++;
}

void MD::PBC(){
    for(int i=0; i<natoms_; i++){
        x_[i] -= std::floor(x_[i] / box_) * box_;
//        x_[i][0] -= box_ * std::floor(x_[i][0]/box_);
//        x_[i][1] -= box_ * std::floor(x_[i][1]/box_);
//        x_[i][2] -= box_ * std::floor(x_[i][2]/box_);
    }
}

double MD::temp() const{
    double ke = 0;
    for(int i=0; i<natoms_; i++){
        ke += mass_ * abs(v_[i]);
//        ke += mass_ * v_[i][0]*v_[i][0];
//        ke += mass_ * v_[i][1]*v_[i][1];
//        ke += mass_ * v_[i][2]*v_[i][2];
    }

    return ke;
}

double MD::distSqr(const int i, const int j) const{
    if(i >= natoms_ || j >= natoms_)
        throw std::runtime_error("Atom index out of bounds");

    MyTypes::vec dist = x_[i] - x_[j];
    return abs(dist);
//    double d[3];
//    d[0] = x_[i][0] - x_[j][0];
//    d[1] = x_[i][1] - x_[j][1];
//    d[2] = x_[i][2] - x_[j][2];
//    d[0] -= box_ * std::rint(d[0]/box_);
//    d[1] -= box_ * std::rint(d[1]/box_);
//    d[2] -= box_ * std::rint(d[2]/box_);

//    return d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
}

void MD::print(int natoms) const{
    if(natoms < 0) natoms = natoms_;

    for(int i=0; i<natoms; i++){
        printf("%1d %8.3f %8.3f %8.3f\n",
//               i, x_[i][0], x_[i][1], x_[i][2]);
               i, x_[i].x, x_[i].y, x_[i].z);
    }
}

void MD::output() const{
    for(const std::unique_ptr<TrjOutput> &trj : trjOutputs_) trj->writeFrame(x_, step_, box_);
}