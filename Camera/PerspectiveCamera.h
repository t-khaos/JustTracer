#pragma once

#include "../Common/Camera.h"

struct PerspectiveCamera : Camera {
    Point3f origin;
    Point3f start;
    Vector3f horizontal;
    Vector3f vertical;

    PerspectiveCamera(Point3f look_from, Point3f look_at, Vector3f up, float fov, float aspect_ratio);

    virtual Ray GetRay(const float &s, const float &t) const override;
};