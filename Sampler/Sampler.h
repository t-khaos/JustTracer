#pragma once

#include "../Random.h"
#include "../Math/Vector2.h"
#include "../Ray.h"

struct Sampler {
    int spp;
    Random random;

    virtual Vector2 Sample(int x, int y) = 0;
};

