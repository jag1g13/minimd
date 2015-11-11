#include <iostream>
#include <ctime>

#include "md.h"

using std::cout;
using std::endl;

int main() {
    const std::clock_t start = std::clock();

    const int nsteps = 1e5;
    const int natoms = 100;
    MD dynamics;
    dynamics.createAtoms(natoms,0);
    dynamics.setup();
    for(int i=0; i<nsteps; i++){
        dynamics.step();

        if(i%10 == 0) dynamics.output();
        if(i%1000 == 0) cout << (100*i)/nsteps << "%\r" << std::flush;
    }
    cout << endl;
    dynamics.print();

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nsteps, static_cast<int>(nsteps/time));
    return 0;
}