//
// Created by james on 27/08/15.
//

#include "LammpsTrjOutput.h"

#include <cstdio>

using std::string;

LammpsTrjOutput::LammpsTrjOutput(const int natoms, const string &filename){
    natoms_ = natoms;
    if(openFile(filename))
        throw std::runtime_error("ERROR: Could not open Lammps Trj file for writing");
}

LammpsTrjOutput::~LammpsTrjOutput(){
    closeFile();
}

int LammpsTrjOutput::openFile(const string &filename){
    backup_old_file(filename);
    file_ = std::fopen(filename.c_str(), "w");
    if(!file_) return 1;
    return 0;
}

int LammpsTrjOutput::closeFile(){
    if(file_) fclose(file_);
    if(!file_) return 0;
    return 1;
}

int LammpsTrjOutput::writeFrame(const MyTypes::vecList &frame, const MyTypes::vecList &dip,
                                const int num, const double box){
    // Print headers
    fprintf(file_, "ITEM: TIMESTEP\n%d\n", num);
    fprintf(file_, "ITEM: NUMBER OF ATOMS\n%d\n", natoms_);
    fprintf(file_, "ITEM: BOX BOUNDS pp pp pp\n%f %f\n%f %f\n%f %f\n",
            0., 10*box, 0., 10*box, 0., 10*box);
    fprintf(file_, "ITEM: ATOMS id type mol x y z mux muy muz mass diameter\n");

    for(int i=0; i < natoms_; i++){
        fprintf(file_, " %6d %4d %4d %10.4f %10.4f %10.4f %9.5f %9.5f %9.5f %4.1f %4.1f\n",
                i+1, i+1, 1,
                10*frame[i].x, 10*frame[i].y, 10*frame[i].z,
                dip[i].x, dip[i].y, dip[i].z,
                1., 1.);
    }
    fflush(file_);

    return 0;
}

int LammpsTrjOutput::writeFrame(const MyTypes::vecList &frame,
                                const int num, const double box){
    // Print headers
    fprintf(file_, "ITEM: TIMESTEP\n%d\n", num);
    fprintf(file_, "ITEM: NUMBER OF ATOMS\n%d\n", natoms_);
    fprintf(file_, "ITEM: BOX BOUNDS pp pp pp\n%f %f\n%f %f\n%f %f\n",
            0., 10*box, 0., 10*box, 0., 10*box);
    fprintf(file_, "ITEM: ATOMS id type mol x y z mux muy muz mass diameter\n");

    for(int i=0; i < natoms_; i++){
        fprintf(file_, " %6d %4d %4d %10.4f %10.4f %10.4f %9.5f %9.5f %9.5f %4.1f %4.1f\n",
                i+1, i+1, 1,
                10*frame[i].x, 10*frame[i].y, 10*frame[i].z,
                0., 0., 0.,
                1., 1.);
    }
    fflush(file_);

    return 0;
}
