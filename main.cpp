#include <iostream>
#include <ctime>

#include "md.h"

using std::cout;
using std::endl;

int main() {
    const int nsteps = 1e6;
    cout << "Hello, World!" << endl;
    const std::clock_t start = std::clock();
    MD dynamics;
    dynamics.createAtoms(2,0);
    dynamics.setupBonded();
    for(int i=0; i<nsteps; i++){
        if(i%1000 == 0){
            dynamics.print();
            cout << dynamics.distSqr(0, 1) << endl;
        }
        dynamics.calcForces();
        dynamics.integrate();
    }
    dynamics.print();
    cout << dynamics.distSqr(0, 1) << endl;

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nsteps, static_cast<int>(nsteps/time));
    return 0;
}