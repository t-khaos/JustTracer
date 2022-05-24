#pragma once

#include "../Common/Object.h"
#include "../Common/Light.h"

struct Rectangle : Object, Light {
    union {
        Vector3d vertices[4];
        struct {
            Vector3d A, B, C, D;
        };
    };

    Vector3d normal;
    double area;
    Vector3d s, t;
    std::shared_ptr<Material> material;

    Rectangle(Vector3d _v0, Vector3d _v1, Vector3d _v2, Vector3d _v3, std::shared_ptr<Material> _mat);

    virtual bool Intersect(const Ray &ray, HitResult &result, double t_near) const override;

    virtual void SampleHitResult(HitResult &result) override;

    virtual double PDF() override;
};