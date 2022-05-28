#pragma once

#include "HitResult.h"
#include "LightResult.h"

struct Light {
    virtual void SampleHitResult(LightResult &result) = 0;

    virtual float PDF() = 0;
};