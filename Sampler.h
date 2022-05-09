#pragma once

#include "Random.h"

struct Sampler{
    int spp;
    Random random;
};

struct TrapezoidalSampler : public Sampler{

};