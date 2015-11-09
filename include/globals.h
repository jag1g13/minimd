//
// Created by james on 09/11/15.
//

#ifndef MINIMD_GLOBALS_H
#define MINIMD_GLOBALS_H

#include <array>
#include <vector>

namespace MyTypes{
    typedef std::array<double, 3> vec;
    typedef std::vector<vec> vecList;
}

namespace MyEnums{
    enum class BondType{BOND=2, ANGLE=3, DIHEDRAL=4};
}

#endif //MINIMD_GLOBALS_H
