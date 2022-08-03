#pragma once

#include <memory>

#include "../Math/Global.h"
#include "Ray.h"
#include "HitResult.h"
#include "../Accelerator/AABB.h"

struct Object {
    AABB bounds;

    virtual bool Intersect(Ray &ray, HitResult &result, float t_near) const = 0;
};



