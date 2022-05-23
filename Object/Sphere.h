#pragma once


#include "../Common/Object.h"
#include "../Common/Light.h"

struct Sphere : Object, Light {

    float radius;
    Vector3f center;
    std::shared_ptr<Material> material;

    Sphere(const float _r, const Vector3f _p, std::shared_ptr<Material> _mat)
            : radius(_r), center(_p), material(_mat) {}

    bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;

    virtual void SampleHitResult(HitResult &result) override;

    virtual float PDF() override;
};