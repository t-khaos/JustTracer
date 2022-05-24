#pragma once

#include "Global.h"
#include "Ray.h"
#include "Global.h"
#include "Vector.h"

struct Camera {
    virtual Ray GetRay(const double &s, const double &t) const = 0;
};

