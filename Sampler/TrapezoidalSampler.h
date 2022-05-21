#pragma once

#include "Sampler.h"

struct TrapezoidalSampler : Sampler {
public:
    TrapezoidalSampler() {}

    virtual Vector2f CastRayByDistribution(int x, int y) override;

private:
    int index = 0;
};

Vector2f TrapezoidalSampler::CastRayByDistribution(int x, int y) {
    index = index >= 4 ? 0 : index;

    int sx = index % 2;
    int sy = index / 2;

    float r1 = 2 * RandomFloat();
    float r2 = 2 * RandomFloat();

    float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    float dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    float s = static_cast<float>(x) + (dx + sx + 0.5) / 2;
    float t = static_cast<float>(y) + (dy + sy + 0.5) / 2;

    index++;

    return Vector2f(s, t);
}