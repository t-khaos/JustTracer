#pragma once

#include <vector>
#include <iostream>

#include "../Common/Global.h"
#include "../Common/Vector.h"

struct Sampler {
    int index = 0;

    Sampler() {}

    Vector2d CastRayByDistribution(int x, int y);
};