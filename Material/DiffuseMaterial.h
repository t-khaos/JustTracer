#pragma once

#include "IMaterial.h"


struct DiffuseMaterial : IMaterial {
    DiffuseMaterial(
            const Color3f &_color,
            const Color3f &_emission,
            const MaterialType &_type = MaterialType::DIFFUSE)
            : IMaterial(_color, _emission, _type) {}


    virtual float PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f SampleDirection(const Vector3f &V, const Vector3f &N) override;
};

inline float DiffuseMaterial::PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    if (Dot(wo, N) > 0.0)
        return 0.5 / PI;
    else
        return 0.0;
}

inline Vector3f DiffuseMaterial::Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    if (Dot(wo, N) > 0.0)
        return base_color / PI;
    else
        return Vector3f(0.f);
}

inline Vector3f DiffuseMaterial::SampleDirection(const Vector3f &V, const Vector3f &N) {
    float phi = 2 * PI * RandomFloat();
    float z = std::fabs(1. - 2. * RandomFloat());//[0,1]
    float radius = std::sqrt(1 - z * z);//[0,1]

    float x = radius * std::cos(phi);
    float y = radius * std::sin(phi);

    Vector3f direction(x, y, z);

    return ToWorld(direction, N);
}
