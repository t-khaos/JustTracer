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

    double r1 = 2 * RandomDouble();
    double r2 = 2 * RandomDouble();

    double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    double s = static_cast<double>(x) + (dx + index % 2 + 0.5) / 2;
    double t = static_cast<double>(y) + (dy + index / 2 + 0.5) / 2;

    index++;

    return {s,t};
}