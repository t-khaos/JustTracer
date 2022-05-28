#pragma once

#include <algorithm>
#include "../Common/Material.h"


struct MicrofacetMaterial : Material {

    float roughness = 0;
    float metallic = 0;
    float reflectance = 0;

    MicrofacetMaterial(
            float _rou, float _met, float _ref,
            const Color &_c, const Color &_emi,
            const MaterialType &_type = MaterialType::MIRCOFACET)
            : Material(_c, _emi, _type), roughness(_rou), metallic(_met), reflectance(_ref) {

    }

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Color EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Vector3 SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

};



/* ==================================================================== */
/*                          LearnOpenGL 实现                             */
/* ==================================================================== */


//法线分布函数D
//-------------------------------------------------
inline float DistributionGGX(float NoH, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;

    float nom   = a2;
    float denom = (NoH*NoH * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

//几何项G
//-------------------------------------------------
inline float GeometrySchlickGGX(float NoV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NoV;
    float denom = NoV * (1.0 - k) + k;

    return nom / denom;
}
inline float GeometrySmith(float NoV, float NoL, float roughness)
{
    float ggx2 = GeometrySchlickGGX(NoV, roughness);
    float ggx1 = GeometrySchlickGGX(NoL, roughness);

    return ggx1 * ggx2;
}

//菲涅尔项F
//-------------------------------------------------
inline Vector3 FresnelSchlick(float VoH, Vector3 f0)
{
    return f0 + (1.0f - f0) * std::pow(std::clamp(1.0f - VoH, 0.0f, 1.0f), 5.0f);
}



/* ==================================================================== */
/*                          Filament 实现                             */
/* ==================================================================== */

//法线分布函数D
//-------------------------------------------------
inline float D_GGX(float NoH, float a) {
    float a2 = a * a;
    float f = (NoH * a2 - NoH) * NoH + 1.0;
    return a2 / (PI * f * f);
}

//几何项G和分母化简为遮蔽项V
//-------------------------------------------------
inline float V_SmithGGXCorrelated(float NoV, float NoL, float a) {
    float a2 = a * a;
    float GGX_L = NoV * std::sqrt((-NoL * a2 + NoL) * NoL + a2);
    float GGX_V = NoL * std::sqrt((-NoV * a2 + NoV) * NoV + a2);
    return 0.5 / (GGX_L + GGX_V);
}

//菲涅尔项F
//-------------------------------------------------
inline Vector3 F_Schlick(float u, Vector3 f0) {
    return f0 + (1.0f - f0) * std::pow(1.0f - u, 5.0f);
}
