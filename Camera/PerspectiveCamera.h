#pragma once

#include "Camera.h"
#include "../Tool/Vector3.h"

class PerspectiveCamera : public Camera {
private:
    Point3 origin;
    Point3 start;
    Vec3 horizontal;
    Vec3 vertical;

public:
    PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 up, double fov, double aspect_ratio);

    virtual Ray GetRay(const double &s, const double &t) const override;
};

PerspectiveCamera::PerspectiveCamera(Point3 look_from, Point3 look_at, Vec3 up, double fov, double aspect_ratio) {
    double theta = Degrees2Radians(fov);
    double h = std::tan(theta / 2);

    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    Vec3 w = (look_from - look_at).Normalize();
    Vec3 u = up.Cross(w).Normalize();
    Vec3 v = w.Cross(u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    start = origin - horizontal / 2 - vertical / 2 - w;
}

Ray PerspectiveCamera::GetRay(const double &s, const double &t) const {
    return Ray(origin, start + s * horizontal + t * vertical - origin);
}