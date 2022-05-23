#pragma once

#include <limits>
#include <memory>
#include "Vector.h"
#include "Material.h"

struct Ray {
    Point3f origin;
    Vector3f direction;

    Ray(const Point3f &_ori, const Vector3f &_dir) : origin(_ori), direction((Normalize(_dir))) {}

    Point3f at(float time) const { return origin + direction * time; }
};
