//
// Created by james on 10/11/15.
//

#include "globals.h"

#include <cmath>

//vec3d vec3d(const double x, const double y, const double z){
//    vec3d vec;
//    vec.x = x;
//    vec.y = y;
//    vec.z = z;
//    return vec;
//}

vec3d operator+(const vec3d &a, const vec3d &b){
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}

vec3d operator-(const vec3d &a, const vec3d &b){
    return {a.x-b.x, a.y-b.y, a.z-b.z};
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
    vec.x += b;
    vec.y += b;
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

double abs(const vec3d &vec){
    return std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

vec3d std::floor(const vec3d &vec){
    return {std::floor(vec.x), std::floor(vec.y), std::floor(vec.z)};
}