#pragma once

#include "HitResult.h"

struct Light {
    virtual void SampleHitResult(HitResult &result) = 0;

    virtual double PDF() = 0;
};