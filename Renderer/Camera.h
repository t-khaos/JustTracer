#pragma once

#include "../Math/Global.h"
#include "../Common/Ray.h"
#include "../Math/Global.h"
#include "../Math/Vector.h"

struct Camera {
    Point3 origin;
    Point3 start;
    Vector3 horizontal;
    Vector3 vertical;

    Camera(Point3 look_from, Point3 look_at, Vector3 up, float fov, float aspect_ratio);

    Ray GetRay(const float &s, const float &t) const;
};

