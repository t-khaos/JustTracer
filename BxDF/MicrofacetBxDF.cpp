
#include "MicrofacetBxDF.h"
#include "../Math/Math.h"

float MicrofacetBxDF::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return 0.5 / PI;
}

Color MicrofacetBxDF::Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 H = Normalize(V + L);

    //粗糙度重映射
    float roughnessR = roughness * roughness;

    Color diffuseColor = (1.0f - metallic) * albedo;

    //入射和出射方向与法线的夹角余弦
    float NoV = std::abs(Dot(N, V)) + 1e-5;
    float NoL = std::clamp(Dot(N, L), 0.0f, 1.0f);
    float NoH = std::clamp(Dot(N, H), 0.0f, 1.0f);
    float VoH = std::clamp(Dot(V, H), 0.0f, 1.0f);
    float LoH = std::clamp(Dot(L, H), 0.0f, 1.0f);

    float _D = D_GGX(NoH, roughnessR);
    Vector3 _F = FresnelSchlick(VoH, F0());
    float _V = V_SmithGGXCorrelated(NoV, NoL, roughnessR);

    Color specular = _D * _F * _V;

    Color diffuse = diffuseColor * Fr_Lambert();

    return specular + diffuse;
}

BxDFResult MicrofacetBxDF::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 H = Normalize(V + L);
    float VoH = std::clamp(Dot(V, H), 0.0f, 1.0f);
    Vector3 _F = FresnelSchlick(VoH, F0());
    float probability = ToGrayScale(_F);
    bool isSpecular = probability > RandomFloat();
    Vector3 direction = isSpecular ? DiffuseDirection(N) : SpecularDirection(N, V);
    float pdf = PDF(L, V, N);
    Color fr = Eval(L, V, N);
    return BxDFResult(direction, pdf, fr, isSpecular);
}