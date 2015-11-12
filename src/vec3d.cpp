//
// Created by james on 10/11/15.
//

#include "globals.h"

#include <cmath>

vec3d operator+(const vec3d &a, const vec3d &b){
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}
vec3d operator-(const vec3d &a, const vec3d &b){
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}
vec3d operator*(const vec3d &a, const vec3d &b){
    return {a.x*b.x, a.y*b.y, a.z*b.z};
}
vec3d operator/(const vec3d &a, const vec3d &b){
    return {a.x/b.x, a.y/b.y, a.z/b.z};
}

vec3d &operator+=(vec3d &vec, const vec3d &other){
    vec.x += other.x;
    vec.y += other.y;
    vec.z += other.z;
    return vec;
}

vec3d &operator-=(vec3d &vec, const vec3d &other){
    vec.x -= other.x;
    vec.y -= other.y;
    vec.z -= other.z;
    return vec;
}

vec3d &operator+=(vec3d &vec, const double b){
#pragma omp atomic update
    vec.x += b;
#pragma omp atomic update
    vec.y += b;
#pragma omp atomic update
    vec.z += b;
    return vec;
}
vec3d &operator-=(vec3d &vec, const double b){
    vec.x -= b;
    vec.y -= b;
    vec.z -= b;
    return vec;
}
vec3d &operator*=(vec3d &vec, const double b){
    vec.x *= b;
    vec.y *= b;
    vec.z *= b;
    return vec;
}
vec3d &operator/=(vec3d &vec, const double b){
    vec.x /= b;
    vec.y /= b;
    vec.z /= b;
    return vec;
}
vec3d &operator%=(vec3d &vec, const double b){
    const double binv = 1. / b;
    vec.x -= b * std::rint(vec.x * binv);
    vec.y -= b * std::rint(vec.y * binv);
    vec.z -= b * std::rint(vec.z * binv);
    return vec;
}

vec3d operator+(const vec3d &a, const double b){
    return {a.x+b, a.y+b, a.z+b};
}
vec3d operator-(const vec3d &a, const double b){
    return {a.x-b, a.y-b, a.z-b};
}
vec3d operator*(const vec3d &a, const double b){
    return {a.x*b, a.y*b, a.z*b};
}
vec3d operator/(const vec3d &a, const double b){
    return {a.x/b, a.y/b, a.z/b};
}

void normalize(vec3d &vec){
    vec /= vecabs(vec);
}

double vecabs(const vec3d &vec){
    return std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

double dot(const vec3d &a, const vec3d &b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3d cross(const vec3d &a, const vec3d &b){
    return {a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x};
}

vec3d std::floor(const vec3d &vec){
    return {std::floor(vec.x), std::floor(vec.y), std::floor(vec.z)};
}