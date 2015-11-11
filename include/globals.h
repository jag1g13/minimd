//
// Created by james on 09/11/15.
//

#ifndef MINIMD_GLOBALS_H
#define MINIMD_GLOBALS_H

#include <array>
#include <vector>

typedef struct vec3d{
    double x, y, z, m;
} vec3d;

namespace MyTypes{
    typedef vec3d vec;
    typedef std::vector<vec> vecList;
}

namespace MyEnums{
    enum class BondType{BOND=2, ANGLE=3, DIHEDRAL=4};
}

vec3d operator+(const vec3d &a, const vec3d &b);
vec3d operator-(const vec3d &a, const vec3d &b);
vec3d operator*(const vec3d &a, const vec3d &b);
vec3d operator/(const vec3d &a, const vec3d &b);

vec3d &operator+=(vec3d &vec, const vec3d &other);
vec3d &operator-=(vec3d &vec, const vec3d &other);

vec3d &operator+=(vec3d &vec, const double b);
vec3d &operator-=(vec3d &vec, const double b);
vec3d &operator*=(vec3d &vec, const double b);
vec3d &operator/=(vec3d &vec, const double b);
vec3d &operator%=(vec3d &vec, const double b);

vec3d operator+(const vec3d &a, const double b);
vec3d operator-(const vec3d &a, const double b);
vec3d operator*(const vec3d &a, const double b);
vec3d operator/(const vec3d &a, const double b);

double abs(const vec3d &vec);

namespace std{
    vec3d floor(const vec3d &vec);
}

#endif //MINIMD_GLOBALS_H
