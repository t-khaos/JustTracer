#pragma once

#include <vector>
#include <iostream>

#include "../Math/Global.h"
#include "../Math/Vector.h"

//Distribution Type
enum SamplerType{
    Trapezoidal,
    Uniform,
    Disk,
};

struct Sampler {
    int index = 0;
    SamplerType type;

    Sampler(SamplerType _type):type(_type) {}

    Vector2 CastRayByDistribution(int x, int y);
};