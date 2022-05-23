#pragma once

#include <limits>
#include <memory>
#include "Tool/Vector.h"
#include "Material/IMaterial.h"


struct Ray {
    Point3f origin;
    Vector3f direction;

    Ray(const Point3f &_ori, const Vector3f &_dir) : origin(_ori), direction((Normalize(_dir))) {}

    Point3f at(float time) const { return origin + direction * time; }
};


struct HitResult {
    Point3f point;
    Vector3f normal;
    float distance;

    std::shared_ptr<IMaterial> material = nullptr;

    HitResult() : point(Point3f()), normal(Vector3f()), distance(0.0) {}
};
