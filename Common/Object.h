#pragma once

#include <memory>

#include "Global.h"
#include "Ray.h"
#include "HitResult.h"
#include "AABB.h"

struct Object {
    AABB bounds;

    Object() {}

    virtual bool Intersect(const Ray &ray, HitResult &result, double t_near) const = 0;
};



