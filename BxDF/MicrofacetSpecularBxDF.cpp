
#include "MicrofacetSpecularBxDF.h"

float MicrofacetSpecularBxDF::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 H = Normalize(V + L);

    float roughnessR = roughness * roughness;
    float NoH = std::clamp(Dot(N, H), 0.0f, 1.0f);
    float D = DistributionGGX(NoH, roughnessR);

    return NoH * D;
}

Color MicrofacetSpecularBxDF::Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 h = Normalize(V + L);

    //粗糙度重映射
    float roughnessR = roughness * roughness;

    //入射和出射方向与法线的夹角余弦
    float NoV = std::abs(Dot(N, V)) + 1e-5;
    float NoL = std::clamp(Dot(N, L), 0.0f, 1.0f);
    float NoH = std::clamp(Dot(N, h), 0.0f, 1.0f);
    float VoH = std::clamp(Dot(V, h), 0.0f, 1.0f);

    float D = DistributionGGX(NoH, roughnessR);
    Color F = FresnelSchlick(VoH, F0());
    float G = GeometrySchlickGGX(NoV, roughnessR);

    Vector3 numerator = D * G * F;
    //+0.0001避免除零
    float denominator = 4.0f * std::max(NoV, 0.0f) * std::max(NoL, 0.0f) + 0.0001f;

    Vector3 specular = numerator / denominator;

    return specular;
}

BxDFResult MicrofacetSpecularBxDF::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 direction = SpecularDirection(N, V);
    float pdf = PDF(L, V, N);
    Color fr = Eval(L, V, N);
    return BxDFResult(direction, pdf, fr, true);
}