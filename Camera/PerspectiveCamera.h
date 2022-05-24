#pragma once

#include "../Common/Camera.h"

struct PerspectiveCamera : Camera {
    Point3d origin;
    Point3d start;
    Vector3d horizontal;
    Vector3d vertical;

    PerspectiveCamera(Point3d look_from, Point3d look_at, Vector3d up, double fov, double aspect_ratio);

    virtual Ray GetRay(const double &s, const double &t) const override;
};