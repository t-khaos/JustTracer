#pragma once

#include <vector>
#include "../Tool/Vector.h"
#include "IIntersect.h"
#include "ILight.h"


struct Rectangle : IIntersect, ILight {
    union {
        Vector3f vertices[4];
        struct {
            Vector3f A, B, C, D;
        };
    };

    Vector3f normal;
    float area;
    Vector3f s, t;
    std::shared_ptr<IMaterial> material;

    Rectangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Vector3f _v3, std::shared_ptr<IMaterial> _mat)
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


inline bool Rectangle::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    if (Dot(-ray.direction, normal) < EPSILON)
        return false;

    float time = Dot((A - ray.origin), normal) * (1 / Dot(ray.direction, normal));

    if (time <= 0.f || time > t_near)
        return false;

    Point3f point = ray.at(time);

    //矩形在xyz轴上取值范围
    auto maxVector = MaxVector(MaxVector(A, B), MaxVector(C, D));
    auto minVector = MinVector(MinVector(A, B), MinVector(C, D));
    if (minVector.x - point.x > EPSILON || point.x - maxVector.x > EPSILON ||
        minVector.y - point.y > EPSILON || point.y - maxVector.y > EPSILON ||
        minVector.z - point.z > EPSILON || point.z - maxVector.z > EPSILON)
        return false;

    result.distance = time;
    result.point = point;
    result.normal = normal;
    result.material = material;

    return true;
}

inline void Rectangle::SampleHitResult(HitResult &result) {
    //矩形内均匀采样
    result.point = A + s * RandomFloat() + t * RandomFloat();
    result.material = material;
    result.normal = normal;
}


inline float Rectangle::PDF() {
    return 1 / area;
}