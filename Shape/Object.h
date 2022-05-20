#pragma once

#include <memory>

#include "../Ray.h"

struct Object {
    Object() {}
    virtual bool intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const = 0;
};