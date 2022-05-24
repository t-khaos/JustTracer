#pragma once

#include <memory>

#include "Global.h"
#include "Ray.h"
#include "HitResult.h"
#include "../Accelerator/AABB.h"

struct Object {
    AABB bounds;
    virtual AABB GetBounds();

    Object():bounds(AABB()) {}

    virtual bool Intersect(const Ray &ray, HitResult &result, double t_near) const = 0;
};



