#pragma once

#include <limits>
#include <memory>
#include "../Math/Vector.h"
#include "Material.h"

struct Ray {
    Point3 origin;
    Vector3 direction;

    Ray(const Point3 &_ori, const Vector3 &_dir) : origin(_ori), direction((Normalize(_dir))) {}

    Point3 at(float time) const { return origin + direction * time; }
};
