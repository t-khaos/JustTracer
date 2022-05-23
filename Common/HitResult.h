#pragma once

#include <memory>

#include "Vector.h"
#include "Material.h"

struct HitResult {
    Point3f point;
    Vector3f normal;
    float distance;

    std::shared_ptr<Material> material = nullptr;

    HitResult() : point(Point3f()), normal(Vector3f()), distance(0.0) {}
};