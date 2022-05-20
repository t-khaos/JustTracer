#pragma once

#include <limits>
#include <memory>
#include "Tool/Vector3.h"
#include "Material/Material.h"


struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray(const Point3 &_ori, const Vec3 &_dir) : origin(_ori), direction(_dir.Normalize()) {}

    Point3 at(float time) const { return origin + direction * time; }
};


struct HitResult {
    Point3 point;
    Vec3 normal;
    float distance;

    std::shared_ptr<Material> material = nullptr;

    HitResult() : point(Point3()), normal(Vec3()), distance(0.0) {}
};
