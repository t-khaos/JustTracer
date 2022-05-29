#pragma once

#include "../Common/BxDF.h"

struct MicrofacetBxDF : BxDF {

    float roughness;
    float metallic;
    float reflectance;

    MicrofacetBxDF(float _rou, float _met, float _ref, const Color &_albedo)
            : roughness(_rou), metallic(_met), reflectance(_ref), BxDF(_albedo) {}

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Color Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    Vector3 F0() const { return 0.16f * reflectance * reflectance * (1.0f - metallic) + albedo * metallic; }
};

inline float Fr_Lambert() {
    return 1.0f / PI;
}

inline float D_GGX(float NoH, float a) {
    float a2 = a * a;
    float f = (NoH * a2 - NoH) * NoH + 1.0;
    return a2 / (PI * f * f);
}

inline Vector3 FresnelSchlick(float u, Vector3 f0) {
    return f0 + (1.0f - f0) * pow(1.0f - u, 5.0f);
}

inline float V_SmithGGXCorrelated(float NoV, float NoL, float a) {
    float a2 = a * a;
    float GGX_L = NoV * sqrt((-NoL * a2 + NoL) * NoL + a2);
    float GGX_V = NoL * sqrt((-NoV * a2 + NoV) * NoV + a2);
    return 0.5 / (GGX_V + GGX_L);
}