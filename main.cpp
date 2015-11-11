#include <iostream>
#include <ctime>

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
    const int natoms = 500;
    const double delt = 0.01;
    const double box = 100.;
    const double cutoff = -1.;

    MD dynamics(box);

//    bondLengths_.push_back(make_unique<BondLengthHarmonic>(0, 1, 1, 10));

    dynamics.nonbonds_.push_back(make_unique<NonbondLJ>(natoms, box, cutoff));

//    integrators_.push_back(make_unique<IntegratorVerlet>(natoms, delt_));
    dynamics.integrators_.push_back(make_unique<IntegratorLeapfrog>(natoms, delt));
    dynamics.integrators_.push_back(make_unique<IntegratorLeapfrog>(
            natoms, delt, MyEnums::IntegratorType::ROTATIONAL));

    dynamics.thermostats_.push_back(make_unique<ThermostatVrescale>(1, 1));

    dynamics.trjOutputs_.push_back(make_unique<XTCOutput>(natoms, "out.xtc"));
    dynamics.trjOutputs_.push_back(make_unique<LammpsTrjOutput>(natoms, "out.trj"));

    dynamics.createAtoms(natoms, 0, 45, 55);

    for(int i=0; i<nequil; i++){
        dynamics.step();
        if(i%1 == 0) dynamics.output();
    }

    dynamics.thermostats_.pop_back();

    for(int i=0; i<nprod; i++){
        dynamics.step();
        if(i%1 == 0) dynamics.output();
        if(i%100 == 0) cout << (100*i)/nprod << "%\r" << std::flush;
    }
    cout << endl;
    dynamics.print();

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nequil+nprod, static_cast<int>((nequil+nprod)/time));
    return 0;
}