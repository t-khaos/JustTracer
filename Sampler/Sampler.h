#pragma once

#include <vector>
#include <iostream>
#include "../Tool/Vector.h"


struct Sampler {
    virtual Vector2f CastRayByDistribution(int x, int y) = 0;
};
