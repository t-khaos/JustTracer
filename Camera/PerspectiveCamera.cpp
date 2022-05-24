
#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Point3d look_from, Point3d look_at, Vector3d up, double fov, double aspect_ratio) {
    double theta = Degrees2Radians(fov);
    double h = std::tan(theta / 2);

    double viewport_height = 2 * h;
    double viewport_width = aspect_ratio * viewport_height;

    Vector3d w = Normalize(look_from - look_at);
    Vector3d u = Normalize(Cross(up, w));
    Vector3d v = Cross(w, u);

    origin = look_from;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    start = origin - horizontal / 2.0 - vertical / 2.0 - w;
}

Ray PerspectiveCamera::GetRay(const double &s, const double &t) const {
    return Ray(origin, start + s * horizontal + t * vertical - origin);
}