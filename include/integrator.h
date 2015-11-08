//
// Created by james on 08/11/15.
//

#ifndef MINIMD_INTEGRATOR_H
#define MINIMD_INTEGRATOR_H

class Integrator{
private:
public:
    virtual void integrate() const = 0;
};

#endif //MINIMD_INTEGRATOR_H
