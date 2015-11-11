#include <iostream>
#include <ctime>
#include <fstream>

#include "md.h"

#include "bond-length-harmonic.h"
#include "nonbond-lj.h"
#include "integrator-leapfrog.h"
#include "integrator-verlet.h"
#include "thermostat-vrescale.h"
#include "XTCOutput.h"
#include "LammpsTrjOutput.h"

using std::cout;
using std::endl;

int main() {
    const std::clock_t start = std::clock();

    const int nequil = 1000;
    const int nprod = 10000;
    const int natoms = 600;
    const double delt = 0.001;
    const double box = 1000000.;
    const double cutoff = -1.;

    MD dynamics(box);


    dynamics.nonbonds_.push_back(make_unique<NonbondLJ>(natoms, box, cutoff));

//    for(int i=0; i<natoms; i+=3){
//        dynamics.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i, i+1, 0.5, 100));
//        dynamics.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i, i+2, 0.5, 100));
//        dynamics.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i+1, i+2, 0.5, 100));
//    }

//    integrators_.push_back(make_unique<IntegratorVerlet>(natoms, delt_));
    dynamics.integrators_.push_back(make_unique<IntegratorLeapfrog>(natoms, delt));
//    dynamics.integrators_.push_back(make_unique<IntegratorLeapfrog>(
//            natoms, delt, MyEnums::IntegratorType::ROTATIONAL));

    dynamics.thermostats_.push_back(make_unique<ThermostatVrescale>(1, 1));

    dynamics.trjOutputs_.push_back(make_unique<XTCOutput>(natoms, "out.xtc"));
    dynamics.trjOutputs_.push_back(make_unique<LammpsTrjOutput>(natoms, "out.trj"));

    dynamics.createAtoms(natoms, 0, 45, 55);

    std::ofstream energyFile("energy.dat");

    for(int i=0; i<nequil; i++){
        dynamics.step();
        if(i%1 == 0) dynamics.output();
        energyFile << i << " " << dynamics.energy() << " " << dynamics.pe() << " " << dynamics.ke() << endl;
    }

    dynamics.thermostats_.pop_back();

    for(int i=0; i<nprod; i++){
        dynamics.step();
        if(i%1 == 0) dynamics.output();
        if(i%100 == 0) cout << (100*i)/nprod << "%\r" << std::flush;
        energyFile << i+nequil << " " << dynamics.energy() << " " << dynamics.pe() << " " << dynamics.ke() << endl;
    }
    cout << endl;
    dynamics.print();

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nequil+nprod, static_cast<int>((nequil+nprod)/time));
    return 0;
}