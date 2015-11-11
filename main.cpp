#include <iostream>
#include <ctime>

#include "md.h"

using std::cout;
using std::endl;

int main() {
    const std::clock_t start = std::clock();

    const int nequil = 100;
    const int nprod = 1000;
    const int natoms = 500;
    MD dynamics;
    dynamics.createAtoms(natoms,0);
    dynamics.setup();
    for(int i=0; i<nequil; i++) dynamics.step();
    for(int i=0; i<nprod; i++){
        dynamics.step();
        if(i%10 == 0) dynamics.output();
        if(i%100 == 0) cout << (100*i)/nprod << "%\r" << std::flush;
    }
    cout << endl;
    dynamics.print();

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nequil+nprod, static_cast<int>((nequil+nprod)/time));
    return 0;
}