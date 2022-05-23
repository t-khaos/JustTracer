#pragma once

#include "../Common/Sampler.h"

struct TrapezoidalSampler : Sampler {
    int index = 0;

    TrapezoidalSampler() {}

    virtual Vector2f CastRayByDistribution(int x, int y) override;
};
