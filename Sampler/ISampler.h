#pragma once

#include <vector>
#include <iostream>
#include "../Tool/Vector.h"


struct ISampler {
    virtual Vector2f CastRayByDistribution(int x, int y) = 0;
};
