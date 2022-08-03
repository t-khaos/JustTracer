#pragma once


#include "../Common/Object.h"
#include "../Common/Light.h"

struct Sphere : Object, Light {

    float radius;
    Vector3 center;
    std::shared_ptr<Material> material;

    Sphere(const float _r, const Vector3 _p, std::shared_ptr<Material> _mat);

    bool Intersect(Ray &ray, HitResult &result, float t_near) const override;

    virtual void SampleLight(LightResult &result) override;

    virtual float PDF() override;
};