#pragma once

#include <vector>
#include <iostream>

#include "Global.h"
#include "Vector.h"

struct Sampler {
    virtual Vector2d CastRayByDistribution(int x, int y) = 0;
};