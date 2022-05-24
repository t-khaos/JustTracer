
#include "Sphere.h"
#include "../Common/Random.h"

Sphere::Sphere(const double _r, const Vector3d _p, std::shared_ptr<Material> _mat)
        : radius(_r), center(_p), material(_mat) {

    //构建包围盒
    bounds = AABB(
            center - Vector3d(radius, radius, radius),
            center + Vector3d(radius, radius, radius)
    );

}

bool Sphere::Intersect(const Ray &ray, HitResult &result, double t_near) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vector3d op = ray.origin - center;
    //h=b/2
    double h = Dot(op, ray.direction);
    double det = h * h - Dot(op, op) + radius * radius;
    if (det < 0)
        return false;
    det = sqrt(det);
    double time = -h - det;
    if (time < EPSILON || time > t_near) {
        time = -h + det;
        if (time < EPSILON || time > t_near)
            return false;
    }
    result.time = time;
    result.point = ray.at(time);
    result.normal = Normalize(result.point - center);
    double NoL = Dot(result.normal, ray.direction);
    result.normal = NoL < 0 ? result.normal : -result.normal;
    result.material = material;
    return true;
}

void Sphere::SampleHitResult(HitResult &result) {

    double theta = 2.0 * PI * RandomDouble();
    double phi = PI * RandomDouble();
    Vector3d direction(
            std::cos(phi),
            std::sin(phi) * std::cos(theta),
            std::sin(phi) * std::sin(theta)
    );

    result.point = center + direction * radius;
    result.normal = direction;
    result.material = material;
}

double Sphere::PDF() {
    return 1 / (4 * PI * radius * radius);
}