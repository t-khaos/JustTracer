#pragma once

#include "../Common/Object.h"
#include "../Common/Light.h"

struct Rectangle : Object, Light {
    union {
        Vector3f vertices[4];
        struct {
            Vector3f A, B, C, D;
        };
    };

    Vector3f normal;
    float area;
    Vector3f s, t;
    std::shared_ptr<Material> material;

    Rectangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Vector3f _v3, std::shared_ptr<Material> _mat)
            : A(_v0), B(_v1), C(_v2), D(_v3), material(_mat) {
        s = B - A;
        t = D - A;
        normal = Normalize(Cross(s, t));
        area = Norm(Cross(s, t));
    }

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;

    virtual void SampleHitResult(HitResult &result) override;

    virtual float PDF() override;
};