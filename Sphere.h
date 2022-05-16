#pragma once


#include "Object.h"
#include "Tool/Vector3.h"


struct Sphere : Object {

    double radius;
    Vec3 position;
    Material* material;

    Sphere(const double _r, const Vec3 _p, Material* _mat)
        : radius(_r), position(_p), material(_mat) {}

    bool intersect(const Ray &ray, HitResult &result, double t_min, double t_max) const override;
};


bool Sphere::intersect(const Ray &ray, HitResult &result, double t_min, double t_max) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vec3 op = ray.origin - position;
    //h=b/2
    double h = op.Dot(ray.direction);
    double det = h * h - op.Dot(op) + radius * radius;

    if (det < 0)
        return false;

    det = sqrt(det);

    double root = -h - det;
    if (root < t_min || root > t_max) {
        root = -h + det;
        if (root < t_min || root > t_max)
            return false;
    }

    result.time = root;
    result.point = ray.at(result.time);
    result.normal = (result.point - position).Normalize();
    double NoL = result.normal.Dot(ray.direction);
    result.normal = NoL < 0 ? result.normal : -result.normal;
    result.material = material;

    return true;
}