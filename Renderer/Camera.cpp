
#include "Camera.h"
#include "../Math/Math.h"

Camera::Camera(Point3 look_from, Point3 look_at, Vector3 up, float fov, float aspect_ratio) {
    float theta = DegreesToRadians(fov);
    float h = std::tan(theta / 2);

    float viewport_height = 2 * h;
    float viewport_width = aspect_ratio * viewport_height;

    Vector3 w = Normalize(look_from - look_at);
    Vector3 u = Normalize(Cross(up, w));
    Vector3 v = Cross(w, u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    start = origin - horizontal / 2.0f - vertical / 2.0f - w;
}

Ray Camera::GetRay(const float &s, const float &t) const {
    return Ray(origin, start + s * horizontal + t * vertical - origin);
}