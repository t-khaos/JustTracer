#pragma once

#include "ICamera.h"
#include "../Tool/Vector.h"

class PerspectiveCamera : public ICamera {
private:
    Point3f origin;
    Point3f start;
    Vector3f horizontal;
    Vector3f vertical;

public:
    PerspectiveCamera(Point3f look_from, Point3f look_at, Vector3f up, float fov, float aspect_ratio);

    virtual Ray GetRay(const float &s, const float &t) const override;
};

inline PerspectiveCamera::PerspectiveCamera(Point3f look_from, Point3f look_at, Vector3f up, float fov, float aspect_ratio) {
    float theta = Degrees2Radians(fov);
    float h = std::tan(theta / 2);

    float viewport_height = 2.0 * h;
    float viewport_width = aspect_ratio * viewport_height;

    Vector3f w = Normalize(look_from - look_at);
    Vector3f u = Normalize(Cross(up, w));
    Vector3f v = Cross(w, u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    start = origin - horizontal / 2.f - vertical / 2.f - w;
}

inline Ray PerspectiveCamera::GetRay(const float &s, const float &t) const {
    return Ray(origin, start + s * horizontal + t * vertical - origin);
}