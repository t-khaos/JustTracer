#pragma once

#include "../Tool/Vector.h"
#include "../Shape/Object.h"
#include "../Shape/Triangle.h"


struct Light{
    virtual void Sample(HitResult &result) = 0;
    virtual float PDF() = 0;
};
