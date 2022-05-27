#pragma once

#include "HitResult.h"

struct Light {
    virtual void SampleHitResult(HitResult &result) = 0;

    virtual float PDF() = 0;
};