#pragma once

#include "Global.h"
#include "Ray.h"
#include "Global.h"
#include "Vector.h"

struct Camera {
    virtual Ray GetRay(const float &s, const float &t) const = 0;
};

