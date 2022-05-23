#pragma once

#include <memory>

#include "../Ray.h"

struct IIntersect {
    IIntersect() {}

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const = 0;
};