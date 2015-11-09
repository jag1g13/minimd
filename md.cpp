//
// Created by james on 17/08/15.
//

#include "md.h"

#include <cmath>
#include <random>
#include <XTCOutput.h>

#include "bond-length-harmonic.h"
#include "integrator-leapfrog.h"
#include "integrator-verlet.h"

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
                x_[i][0] = rand(dre) * box_;
                x_[i][1] = rand(dre) * box_;
                x_[i][2] = rand(dre) * box_;
    }

    if(temp != 0.){
        createVelocity(temp);
    }else{
        for(int i=0; i < natoms_; i++){
            v_[i][0] = 0.;
            v_[i][1] = 0.;
            v_[i][2] = 0.;
        }
    }

    for(int i=0; i < natoms_; i++){
        xm_[i][0] = x_[i][0] - v_[i][0] * delt_;
        xm_[i][1] = x_[i][1] - v_[i][1] * delt_;
        xm_[i][2] = x_[i][2] - v_[i][2] * delt_;
    }
}

void MD::createVelocity(const double temp){
    std::default_random_engine dre(0);
    std::uniform_real_distribution<double> rand(0, 1);

    double sumv[3] = {0., 0., 0.}, sumv2[3] = {0., 0., 0.};
    for(int i=0; i < natoms_; i++){
        v_[i][0] = rand(dre) - 0.5;
        v_[i][1] = rand(dre) - 0.5;
        v_[i][2] = rand(dre) - 0.5;

        sumv[0] += v_[i][0];
        sumv[1] += v_[i][1];
        sumv[2] += v_[i][2];
        sumv2[0] += v_[i][0] * v_[i][0];
        sumv2[1] += v_[i][1] * v_[i][1];
        sumv2[2] += v_[i][2] * v_[i][2];
    }

    sumv[0] /= natoms_;
    sumv[1] /= natoms_;
    sumv[2] /= natoms_;
    sumv2[0] /= natoms_;
    sumv2[1] /= natoms_;
    sumv2[2] /= natoms_;

    const double abssumv2 = std::sqrt(sumv2[0] + sumv2[1] + sumv2[2]);
    const double scale = std::sqrt(3*temp_ / abssumv2);

    for(int i=0; i < natoms_; i++){
        v_[i][0] = (v_[i][0] - sumv[0]) * scale;
        v_[i][1] = (v_[i][1] - sumv[1]) * scale;
        v_[i][2] = (v_[i][2] - sumv[2]) * scale;

    }
}

void MD::calcForces(){
    lj();
//    bonded();
}

void MD::lj(){
//    double cut2i = 1. / (cutoff_*cutoff_);
//    double cut6i = cut2i*cut2i*cut2i;
//    ecut_ = 4 * cut6i * (cut6i - 1);

    for(int i=0; i<natoms_; i++){
        f_[i][0] = 0.;
        f_[i][1] = 0.;
        f_[i][2] = 0.;
    }

    for(int i=0; i < natoms_; i++){
        for(int j=i+1; j < natoms_; j++){
            double r2 = distSqr(i, j);
            double r2i = 1. / r2;
            double r6i = r2i*r2i*r2i * std::pow(sigma_, 6);
            double ff = 48 * epsilon_ * r2i * r6i * (r6i - 0.5);
            f_[i][0] += ff * (x_[i][0]-x_[j][0]);
            f_[i][1] += ff * (x_[i][1]-x_[j][1]);
            f_[i][2] += ff * (x_[i][2]-x_[j][2]);
            f_[j][0] -= ff * (x_[i][0]-x_[j][0]);
            f_[j][1] -= ff * (x_[i][1]-x_[j][1]);
            f_[j][2] -= ff * (x_[i][2]-x_[j][2]);
        }
    }
}

void MD::bonded(){
    for(const std::unique_ptr<BondLength> &bond : bondLengths_) bond->calcForces(x_, f_);
}

void MD::setup(){
    bondLengths_.push_back(make_unique<BondLengthHarmonic>(0, 1, 1, 10));
//    bondLengths_.push_back(make_unique<BondLengthHarmonic>(1, 2, 1, 10));

//    integrators_.push_back(make_unique<IntegratorVerlet>());
    integrators_.push_back(make_unique<IntegratorLeapfrog>());

    trjOutputs_.push_back(make_unique<XTCOutput>(natoms_, "out.xtc"));
}

void MD::removeCOMM(){

}

void MD::integrate(){
    for(const std::unique_ptr<Integrator> &intg : integrators_)
        intg->integrate(natoms_, delt_, x_, xm_, v_, f_);
    step_++;
}

void MD::PBC(){
    for(int i=0; i<natoms_; i++){
        for(int j=0; j<3; j++){
            x_[i][j] -= box_ * std::floor(x_[i][j]/box_);

//            if(x_[i][j] < 0){
//                x_[i][j] += box_;
//                xm_[i][j] += box_;
//            }
//            if(x_[i][j] >= box_){
//                x_[i][j] -= box_;
//                xm_[i][j] -= box_;
//            }
        }
    }
}

double MD::temp() const{
    double ke = 0;
    for(int i=0; i<natoms_; i++){
        ke += mass_ * v_[i][0]*v_[i][0];
        ke += mass_ * v_[i][1]*v_[i][1];
        ke += mass_ * v_[i][2]*v_[i][2];
    }

    return ke;
}

double MD::distSqr(const int i, const int j) const{
    if(i >= natoms_ || j >= natoms_)
        throw std::runtime_error("Atom index out of bounds");

    double d[3];
    d[0] = x_[i][0] - x_[j][0];
    d[1] = x_[i][1] - x_[j][1];
    d[2] = x_[i][2] - x_[j][2];
//    d[0] -= box_ * std::rint(d[0]/box_);
//    d[1] -= box_ * std::rint(d[1]/box_);
//    d[2] -= box_ * std::rint(d[2]/box_);

    return d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
}

void MD::print(int natoms) const{
    if(natoms < 0) natoms = natoms_;

    for(int i=0; i<natoms; i++){
        printf("%1d %8.3f %8.3f %8.3f\n",
               i, x_[i][0], x_[i][1], x_[i][2]);
    }
}

void MD::output() const{
    for(const std::unique_ptr<TrjOutput> &trj : trjOutputs_) trj->writeFrame(x_, step_, box_);
}