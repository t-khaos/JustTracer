#pragma once

#include "../Math/Vector.h"
#include "../Math/Global.h"
#include "../Math/Random.h"

struct BxDFResult {
    Vector3 direction;
    float pdf;
    Color fr;
    bool isDelta;

    BxDFResult(Vector3 _dir, float _pdf, Color _fr, bool _flag)
            : direction(_dir), pdf(_pdf), fr(_fr), isDelta(_flag) {}
};


struct BxDF {
    Color albedo;

    BxDF(const Color &_albedo) : albedo(_albedo) {}

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const = 0;

    virtual Color Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const = 0;

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const = 0;

};

inline Vector3 DiffuseDirection(const Vector3 &N) {
    float phi = 2 * PI * RandomFloat();
    float z = std::fabs(1.0f - 2 * RandomFloat());//[0,1]
    float radius = std::sqrt(1.0f - z * z);//[0,1]

    float x = radius * std::cos(phi);
    float y = radius * std::sin(phi);

    Vector3 direction(x, y, z);

    return ToWorld(direction, N);
}

inline Vector3 SpecularDirection(const Vector3 &N, const Vector3 &V) {
    return (-V) - 2 * Dot((-V), N) * N;
}








