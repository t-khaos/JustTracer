#pragma once

#include "IMaterial.h"

struct RefractMaterial : IMaterial {
    RefractMaterial(
            const Color3f &_color,
            const Color3f &_emission,
            const MaterialType &_type = MaterialType::REFRACT)
            : IMaterial(_color, _emission, _type) {}

    virtual float PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f SampleDirection(const Vector3f &V, const Vector3f &N) override;

};

inline float RefractMaterial::PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    return 1;
}

inline Vector3f RefractMaterial::Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    return base_color;
}

inline Vector3f RefractMaterial::SampleDirection(const Vector3f &V, const Vector3f &N) {
    return Reflect(V, N);
}