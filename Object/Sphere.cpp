
#include "Sphere.h"
#include "../Math/Random.h"

Sphere::Sphere(const float _r, const Vector3 _p, std::shared_ptr<Material> _mat)
        : radius(_r), center(_p), material(_mat) {

    //构建包围盒
    bounds = AABB(
            center - Vector3(radius, radius, radius),
            center + Vector3(radius, radius, radius)
    );
}

bool Sphere::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vector3 op = ray.origin - center;
    //h=b/2
    float h = Dot(op, ray.direction);
    float det = h * h - Dot(op, op) + radius * radius;
    if (det < 0)
        return false;
    det = sqrt(det);
    float time = -h - det;
    if (time < EPSILON || time > t_near) {
        time = -h + det;
        if (time < EPSILON || time > t_near)
            return false;
    }
    result.time = time;
    result.point = ray.at(time);
    result.normal = Normalize(result.point - center);
    float NoL = Dot(result.normal, ray.direction);
    result.normal = NoL < 0 ? result.normal : -result.normal;
    result.material = material;
    result.isLight = material->type == MaterialType::Light;
    return true;
}

void Sphere::SampleHitResult(HitResult &result) {

    float theta = 2.0 * PI * RandomFloat();
    float phi = PI * RandomFloat();
    Vector3 direction(
            std::cos(phi),
            std::sin(phi) * std::cos(theta),
            std::sin(phi) * std::sin(theta)
    );

    result.point = center + direction * radius;
    result.normal = direction;
    result.material = material;
}

float Sphere::PDF() {
    return 1 / (4 * PI * radius * radius);
}