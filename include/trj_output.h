//
// Created by james on 20/08/15.
//

#ifndef CGTOOL_TRJOUTPUT_H
#define CGTOOL_TRJOUTPUT_H

#include <string>

#include <sys/stat.h>

#include "globals.h"

class TrjOutput{
protected:
    /** \brief Number of atoms to be written to output. */
    int natoms_;

    /** \brief Open and prepare output file. */
    virtual int openFile(const std::string &filename) = 0;
    /** \brief Close output file. */
    virtual int closeFile() = 0;

public:
    /** \brief Write a Frame to output file.  Pure virtual function. */
    virtual int writeFrame(const MyTypes::vecList &frame, const int num, const double box) = 0;

    /** \brief Empty destructor to be overwritten. */
    virtual ~TrjOutput(){};
};

inline bool file_exists(const std::string name){
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}


inline bool backup_old_file(const std::string name){
    if(!file_exists(name)) return true;

    std::string newName = "#" + name + "#";
    int i = 1;
    while(file_exists((newName+std::to_string(i)).c_str())) i++;
    int check = std::rename(name.c_str(), (newName+std::to_string(i)).c_str());
    if(check == 0) return true;
    throw std::runtime_error("File could not be backed up");
}


#endif //CGTOOL_TRJOUTPUT_H
