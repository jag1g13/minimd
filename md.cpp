//
// Created by james on 17/08/15.
//

#include "md.h"

#include <cmath>
#include <stdexcept>

void MD::createAtoms(const int natoms){
    natoms_ = natoms;
    x_.resize(natoms_);
    v_.resize(natoms_);
    f_.resize(natoms_);

    double gridN = std::ceil(std::pow(natoms_, 1./3.));
    int done = 0;
    double sumv[3] = {0., 0., 0.}, sumv2[3] = {0., 0., 0.};
    for(int i=0; i < gridN && done < natoms_; i++){
        for(int j=0; j < gridN && done < natoms_; j++){
            for(int k=0; k < gridN && done < natoms_; k++){
                x_[done][0] = i * box_ / gridN;
                x_[done][1] = j * box_ / gridN;
                x_[done][2] = k * box_ / gridN;

                v_[done][0] = std::rand() - 0.5;
                v_[done][1] = std::rand() - 0.5;
                v_[done][2] = std::rand() - 0.5;

                sumv[0] += v_[done][0];
                sumv[1] += v_[done][1];
                sumv[2] += v_[done][2];
                sumv2[0] += v_[done][0]*v_[done][0];
                sumv2[1] += v_[done][1]*v_[done][1];
                sumv2[2] += v_[done][2]*v_[done][2];
            }
        }
    }

    sumv /= natoms_;
    sumv2 /= natoms_;
    double scale = std::sqrt(3*temp_ / sumv2);

    for(int i=0; i < natoms_; i++){
        v_[i][0] = (v_[i][0] - sumv[0]) * scale;
        v_[i][1] *= scale;
        v_[i][2] *= scale;
    }
}

void MD::setBox(const double box){
    box_ = box;
}

void MD::lj(){
    double cut2i = 1. / (cutoff_*cutoff_);
    double cut6i = cut2i*cut2i*cut2i;
    ecut_ = 4 * cut6i * (cut6i - 1);

    for(int i=0; i < natoms_; i++){
        f_[i][0] = f_[i][1] = f_[i][2] = 0.;
        for(int j=0; j < natoms_; j++){
            double r2 = distSqr(i, j);
            if(r2 <= cutoff_*cutoff_){
                double r2i = 1. / r2;
                double r6i = r2i*r2i*r2i;
                double ff = 48 * r2i * r6i * (r6i - 0.5);
                f_[i][0] += ff * (x_[i][0]-x_[j][0]);
                f_[i][1] += ff * (x_[i][1]-x_[j][1]);
                f_[i][2] += ff * (x_[i][2]-x_[j][2]);
                en_ += 4 * r6i * (r6i - 1) - ecut_;
            }
        }
    }
}

void MD::integrate(){
    double sumv = 0., sumv2 = 0.;
    for(int i=0; i<natoms_; i++){
        double xx[3];
        xx[0] = 2*x_[i][0] - xm_[i][0] + delt_*delt_*f_[i][0];
    }
}

double MD::temp() const{
    double ke = 0;
    for(int i=0; i<natoms_; i++){
        ke += v_[i][0]*v_[i][0];
        ke += v_[i][1]*v_[i][1];
        ke += v_[i][2]*v_[i][2];
    }
    ke /= 2.;

    return -1;
}

double MD::distSqr(const int i, const int j){
    if(i <= natoms_ || j <= natoms_)
        throw std::runtime_error("Atom index out of bounds");

    double d[3];
    d[0] = x_[i][0] - x_[j][0];
    d[1] = x_[i][1] - x_[j][1];
    d[2] = x_[i][2] - x_[j][2];
    d[0] -= box_ * std::rint(d[0]/box_);
    d[1] -= box_ * std::rint(d[1]/box_);
    d[2] -= box_ * std::rint(d[2]/box_);

    return d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
}