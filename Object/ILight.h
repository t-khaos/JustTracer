#pragma once

#include "../Tool/Vector.h"
#include "IIntersect.h"
#include "Triangle.h"


struct ILight{
    virtual void SampleHitResult(HitResult &result) = 0;
    virtual float PDF() = 0;
};
