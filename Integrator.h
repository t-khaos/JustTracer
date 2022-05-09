#pragma once


#include "Vector.hpp"
#include "Ray.hpp"


struct Integrator{
    Integrator(){}

    virtual Color Li(const Ray& ray)=0;
};