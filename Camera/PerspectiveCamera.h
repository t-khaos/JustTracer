#pragma once

#include "Camera.h"

struct PerspectiveCamera : Camera {
    Point3 origin;
    Point3 start;

    Vec3 horizontal;
    Vec3 vertical;

    PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 up, double fov, double aspect_ratio);

    virtual Ray GetRay(const Point2 &target) const override;
};

PerspectiveCamera::PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 up, double fov, double aspect_ratio) {
    double theta = degrees_to_radians(fov);
    double h = std::tan(theta / 2);

    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    Vec3 w = (look_from - look_at).normalize();
    Vec3 u = up.cross(w).normalize();
    Vec3 v = w.cross(u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    start = origin - horizontal / 2 - vertical / 2 - w;
}

Ray PerspectiveCamera::GetRay(const Point2 &target) const {
    return Ray(origin, start + target.s * horizontal + target.t * vertical - origin);
}