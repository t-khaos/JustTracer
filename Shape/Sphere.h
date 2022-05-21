#pragma once


#include "Object.h"
#include "../Tool/Vector.h"


struct Sphere : Object {

    float radius;
    Vector3f center;
    std::shared_ptr<Material> material;

    Sphere(const float _r, const Vector3f _p, std::shared_ptr<Material> _mat)
            : radius(_r), center(_p), material(_mat) {}

    bool intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const override;

    float PDF() {
        return 1 / (4 * PI * radius * radius);
    }
};


bool Sphere::intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vector3f op = ray.origin - center;
    //h=b/2
    float h = Dot(op, ray.direction);
    float det = h * h - Dot(op, op) + radius * radius;
    if (det < 0)
        return false;
    det = sqrt(det);
    float root = -h - det;
    if (root < t_min || root > t_max) {
        root = -h + det;
        if (root < t_min || root > t_max)
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