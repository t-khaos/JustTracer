#pragma once

#include <memory>

#include "../Ray.h"

struct Object {
    Object() {}

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const = 0;
};