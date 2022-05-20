#pragma once

#include "Sampler.h"

struct TrapezoidalSampler : Sampler {
public:
    TrapezoidalSampler(){}
    virtual Vec2 CastRayByDistribution(int x, int y) override;
private:
    int index = 0;
};

Vec2 TrapezoidalSampler::CastRayByDistribution(int x, int y) {
    index = index>=4?0:index;

    float r1 = 2 * RandomFloat();
    float r2 = 2 * RandomFloat();

    float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    float dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    float s = static_cast<float>(x) + (dx + index % 2 + 0.5) / 2;
    float t = static_cast<float>(y) + (dy + index / 2 + 0.5) / 2;

    index++;

    return {s,t};
}