#pragma once

#include <memory>

#include "../Math/Vector.h"
#include "Material.h"

struct HitResult {
    Point3d point;
    Vector3d normal;

    union{
        double distance;
        double time;
    };

    std::shared_ptr<Material> material = nullptr;

    HitResult() : point(Point3d()), normal(Vector3d()), distance(0.0) {}
};