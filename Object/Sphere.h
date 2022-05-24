#pragma once


#include "../Common/Object.h"
#include "../Common/Light.h"

struct Sphere : Object, Light {

    double radius;
    Vector3d center;
    std::shared_ptr<Material> material;

    Sphere(const double _r, const Vector3d _p, std::shared_ptr<Material> _mat);

    bool Intersect(const Ray &ray, HitResult &result, double t_near) const override;

    virtual void SampleHitResult(HitResult &result) override;

    virtual double PDF() override;
};