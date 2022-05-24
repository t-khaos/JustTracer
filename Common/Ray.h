#pragma once

#include <limits>
#include <memory>
#include "../Math/Vector.h"
#include "Material.h"

struct Ray {
    Point3d origin;
    Vector3d direction;

    Ray(const Point3d &_ori, const Vector3d &_dir) : origin(_ori), direction((Normalize(_dir))) {}

    Point3d at(double time) const { return origin + direction * time; }
};
