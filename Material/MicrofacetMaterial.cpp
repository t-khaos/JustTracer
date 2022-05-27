
#include "MicrofacetMaterial.h"

float MicrofacetMaterial::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 H = Normalize(V+L);

    float roughnessR = roughness * roughness;
    float NoH = std::clamp(Dot(N, H), 0.0f, 1.0f);
    float D = D_GGX(NoH, roughnessR);

    return NoH*D;
}

Vector3 MicrofacetMaterial::SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
/*    Vector3 v = -wo;
    Vector3 l = wi;
    Vector3 h = Normalize(v + l);
    float LoH = std::clamp(Dot(l, h), 0.0f, 1.0f);
    Vector3 F = F_Schlick(LoH,F0());*/
    float r = RandomFloat();
    if(r > metallic)
        return SampleDiffuseDirection(N);
    else
        return SampleReflectDirection(V,N);
}

Color MicrofacetMaterial::EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    /* ==================================================================== */
    /*                         Filament PBR Document                        */
    /* ==================================================================== */

    //—————————————————
    //   wi   n    wo
    //   ↘    ↑    ↗
    //—————————————————
    //   l    n    v
    //   ↖    ↑    ↗
    //—————————————————

    Vector3 h = Normalize(V+L);

    //粗糙度重映射
    float roughnessR = roughness * roughness;

    //入射和出射方向与法线的夹角余弦
    float NoV = std::abs(Dot(N,V)) + 1e-5;
    float NoL = std::clamp(Dot(N, L), 0.0f, 1.0f);
    float NoH = std::clamp(Dot(N, h), 0.0f, 1.0f);
    float VoH = std::clamp(Dot(V, h), 0.0f, 1.0f);

    float D = DistributionGGX(NoH, roughnessR);
    Color F = FresnelSchlick(VoH, F0());
    float G = GeometrySchlickGGX(NoV, roughnessR);

    Vector3 numerator = D * G * F;
    //+0.0001避免除零
    float denominator = 4.8f * std::max(NoV,0.0f) *std::max(NoL,0.0f) + 0.0001;

    Vector3 specular = numerator / denominator;

    Vector3 Ks = F;
    Vector3 Kd = 1.0f - Ks;

    Kd *= 1-metallic;

    Vector3 diffuse = baseColor * Kd / PI;

    return diffuse + specular;
}


