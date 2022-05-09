#pragma once


#include "../Math/Vector3.h"
#include "../Ray.h"


struct Integrator{
    Integrator(){}

    virtual Color Li(const Ray& ray)=0;
};