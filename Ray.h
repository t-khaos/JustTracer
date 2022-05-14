#pragma once

#include <limits>
#include <memory>
#include "Tool/Vector3.h"


struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray(const Point3 &_ori, const Vec3 &_dir) : origin(_ori), direction(_dir.normalize()) {}

    Point3 at(double time) const { return origin + direction * time; }
};


struct HitResult {
    Point3 point;
    Vec3 normal;
    double time;

    HitResult() : point(Point3()), normal(Vec3()), time(0.0) {}
};
