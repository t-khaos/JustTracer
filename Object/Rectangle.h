#pragma once

#include "../Common/Object.h"
#include "../Common/Light.h"

struct Rectangle : Object, Light {
    union {
        Vector3 vertices[4];
        struct {
            Vector3 A, B, C, D;
        };
    };

    Vector3 normal;
    float area;
    Vector3 s, t;
    std::shared_ptr<Material> material;

    Rectangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, Vector3 _v3, std::shared_ptr<Material> _mat);

    virtual bool Intersect(Ray &ray, HitResult &result, float t_near) const override;

    virtual void SampleLight(LightResult &result) override;

    virtual float PDF() override;
};