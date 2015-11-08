//
// Created by james on 08/11/15.
//

#ifndef MINIMD_INTEGRATOR_LEAPFROG_H
#define MINIMD_INTEGRATOR_LEAPFROG_H

#include "integrator.h"

class IntegratorLeapfrog : public Integrator{
public:
    void integrate() const;
};

#endif //MINIMD_INTEGRATOR_LEAPFROG_H
