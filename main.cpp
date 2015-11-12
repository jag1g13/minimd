#include <iostream>
#include <ctime>
#include <fstream>
#include <random>

#include "md.h"

#include "bond-length-harmonic.h"
#include "bond-angle-dipole.h"
#include "nonbond-lj.h"
#include "integrator-leapfrog.h"
#include "integrator-leapfrog-rotation.h"
#include "integrator-verlet.h"
#include "thermostat-vrescale.h"
#include "XTCOutput.h"
#include "LammpsTrjOutput.h"

using std::cout;
using std::endl;

int main() {
    const std::clock_t start = std::clock();

    const int nequil = 1000;
    const int nprod = 5000;
    const int natoms = 3;
    const double delt = 0.001;
    const double box = -10.;
    const double cutoff = -1.;

    MD dyn(box);

//    dyn.nonbonds_.push_back(make_unique<NonbondLJ>(natoms, box, cutoff));

    for(int i=0; i<natoms-2; i+=3){
        dyn.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i, i+1, 0.5, 100, box));
        dyn.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i, i+2, 0.5, 100, box));
        dyn.bondLengths_.push_back(make_unique<BondLengthHarmonic>(i+1, i+2, 0.5, 100, box));
        dyn.bondAngles_.push_back(make_unique<BondAngleDipole>(i, i, i+1, 0, 100, box));
    }

    dyn.integrators_.push_back(make_unique<IntegratorLeapfrog>(natoms, delt));
    dyn.integrators_.push_back(make_unique<IntegratorLeapfrogRotation>(natoms, delt));

    dyn.thermostats_.push_back(make_unique<ThermostatVrescale>(5));

    dyn.trjOutputs_.push_back(make_unique<XTCOutput>(natoms, "out.xtc"));
    dyn.trjOutputs_.push_back(make_unique<LammpsTrjOutput>(natoms, "out.trj"));

    dyn.createAtoms(natoms, 0, 0, 10);

    std::ofstream energyFile("energy.dat");
    energyFile << "step total pe ke cartke rotke" << endl;

    for(int i=0; i<nequil; i++){
        dyn.step();
        if(i%1 == 0) dyn.output();
        if((100*i)%nequil == 0) cout << (100*i)/nequil << "%\r" << std::flush;
    }
    cout << "Finished equilibration" << endl;

    dyn.thermostats_.pop_back();

    for(int i=0; i<nprod; i++){
        dyn.step();
        if(i%1 == 0) dyn.output();
        if(i%(nprod/100) == 0) cout << (100*i)/nprod << "%\r" << std::flush;
        energyFile << i << " " << dyn.energy() << " " << dyn.pe() << " " << dyn.ke() << " "
                   << dyn.cartke() << " " << dyn.rotke() << endl;
    }
    cout << "Finished simulation" << endl;

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nequil+nprod, static_cast<int>((nequil+nprod)/time));
    return 0;
}