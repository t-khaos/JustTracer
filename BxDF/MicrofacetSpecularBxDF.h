#pragma once

#include "BxDF.h"

struct MicrofacetSpecularBxDF : BxDF {

    float roughness;
    float metallic;
    float reflectance;

    MicrofacetSpecularBxDF(float _rou, float _met, float _ref, const Color &_albedo)
            : roughness(_rou), metallic(_met), reflectance(_ref), BxDF(_albedo) {}

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Color Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    Vector3 F0() const { return 0.16f * reflectance * reflectance * (1 - metallic) + albedo * metallic; }
};

//法线分布函数D
//-------------------------------------------------
inline float DistributionGGX(float NoH, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;

    float nom = a2;
    float denom = (NoH * NoH * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

//几何项G
//-------------------------------------------------
inline float GeometrySchlickGGX(float NoV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NoV;
    float denom = NoV * (1.0 - k) + k;

    return nom / denom;
}

inline float GeometrySmith(float NoV, float NoL, float roughness) {
    float ggx2 = GeometrySchlickGGX(NoV, roughness);
    float ggx1 = GeometrySchlickGGX(NoL, roughness);

    return ggx1 * ggx2;
}

//菲涅尔项F
//-------------------------------------------------
inline Vector3 FresnelSchlick(float VoH, Vector3 f0) {
    return f0 + (1.0f - f0) * std::pow(std::clamp(1.0f - VoH, 0.0f, 1.0f), 5.0f);
}