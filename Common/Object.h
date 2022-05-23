#pragma once

#include <memory>

#include "Global.h"
#include "Ray.h"
#include "HitResult.h"

struct Object {
    Object() {}

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const = 0;
};



