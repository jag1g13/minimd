//
// Created by james on 17/08/15.
//

#ifndef MINIMD_MD_H
#define MINIMD_MD_H

#include <vector>

class MD{
private:
    std::vector<double[3]> x_;
    std::vector<double[3]> xm_;
    std::vector<double[3]> v_;
    std::vector<double[3]> f_;
    double box_;
    int natoms_;
    double en_;
    double temp_= 300.;
    double delt_ = 0.01;

    double sigma_ = 1.;
    double epsilon_ = 1.;
    double mass_ = 1.;
    double cutoff_ = 10.;
    double ecut_;

    double distSqr(const int i, const int j);

public:
    MD(){};
    ~MD(){};

    void createAtoms(const int natoms);

    void setBox(const double box);

    void lj();

    void integrate();

    double temp() const;
};

#endif //MINIMD_MD_H
