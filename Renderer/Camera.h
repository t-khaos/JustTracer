#pragma once

#include "../Math/Global.h"
#include "../Common/Ray.h"
#include "../Math/Global.h"
#include "../Math/Vector.h"

struct Camera {
    Point3d origin;
    Point3d start;
    Vector3d horizontal;
    Vector3d vertical;

    Camera(Point3d look_from, Point3d look_at, Vector3d up, double fov, double aspect_ratio);

    Ray GetRay(const double &s, const double &t) const;
};

