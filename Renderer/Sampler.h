#pragma once

#include <vector>
#include <iostream>

#include "../Common/Global.h"
#include "../Common/Vector.h"

//Distribution Type
enum SamplerType{
    Trapezoidal,
    Uniform
};

struct Sampler {
    int index = 0;
    SamplerType type;

    Sampler(SamplerType _type):type(_type) {}

    Vector2d CastRayByDistribution(int x, int y);
};