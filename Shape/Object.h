#pragma once

#include <memory>

#include "../Ray.h"

struct Object {
    Object() {}

    virtual bool intersect(const Ray &ray, HitResult &result, float t_near) const = 0;
};