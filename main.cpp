#include <iostream>
#include <ctime>

#include "md.h"

using std::cout;
using std::endl;

int main() {
    cout << std::boolalpha;
    cout << std::is_pod<vec3d>::value << endl;

    const int nsteps = 1e5;
    cout << "Hello, World!" << endl;
    const std::clock_t start = std::clock();
    MD dynamics;
    dynamics.createAtoms(50,0);
    dynamics.setup();
    for(int i=0; i<nsteps; i++){
        dynamics.calcForces();
        dynamics.integrate();
        dynamics.PBC();

        if(i%10 == 0) dynamics.output();
    }
    dynamics.print();

    const double time = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
    printf("Took %5.3f seconds for %d steps\n%d steps per second\n",
           time, nsteps, static_cast<int>(nsteps/time));
    return 0;
}