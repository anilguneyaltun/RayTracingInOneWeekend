//
// Created by anilguneyaltun on 12.09.2021.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP
#include "vec3.hpp"

class ray{

public:
    ray() {}
    ray(const vec3 &a, const vec3 &b) {A = a, B = b;}
    vec3 origin() const{return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t) const {return A + t*B;}

    vec3 A;
    vec3 B;
};

#endif //RAYTRACING_RAY_HPP
