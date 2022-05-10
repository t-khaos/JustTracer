#pragma once

#include "../Ray.h"
#include "../Math.h"
#include "../Math/Vector2.h"

struct Camera {
    Camera() {}

    virtual ~Camera() {}

    virtual Ray GetRay(const Point2 &target) const = 0;
};