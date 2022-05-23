
#include "Sphere.h"

bool Sphere::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vector3f op = ray.origin - center;
    //h=b/2
    float h = Dot(op, ray.direction);
    float det = h * h - Dot(op, op) + radius * radius;
    if (det < 0)
        return false;
    det = sqrt(det);
    float root = -h - det;
    if (root < EPSILON || root > t_near) {
        root = -h + det;
        if (root < EPSILON || root > t_near)
            return false;
    }
    result.distance = root;
    result.point = ray.at(result.distance);
    result.normal = Normalize(result.point - center);
    float NoL = Dot(result.normal, ray.direction);
    result.normal = NoL < 0 ? result.normal : -result.normal;
    result.material = material;
    return true;
}

void Sphere::SampleHitResult(HitResult &result) {

    float theta = 2.0 * PI * RandomFloat();
    float phi = PI * RandomFloat();
    Vector3f direction(
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