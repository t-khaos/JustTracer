#pragma once

#include <algorithm>
#include "../Common/Material.h"


struct MicrofacetMaterial : Material {

    float perceptualRoughness  = 0;
    float metallic = 0;
    float reflectance = 0;

    MicrofacetMaterial(const Color &_color,
                       const Color &_emission,
                       const MaterialType &_type = MaterialType::MICROFACET)
            : Material(_color, _emission, _type) {}

    virtual float PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const override;

    virtual Color EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &normal)const override;

    virtual Vector3 SampleDirection(const Vector3 &wi, const Vector3 &N)const override;

};

//法线分布函数
inline float D_GGX(float NoH, float a){
    float a2 = a * a;
    float f = (NoH * a2 - NoH) * NoH + 1.0;
    return a2 / (PI * f * f);
}


inline float V_SmithGGXCorrelated(float NoV, float NoL, float a){
    float a2 = a * a;
    float GGX_L = NoV * std::sqrt((-NoL * a2 + NoL) * NoL + a2);
    float GGX_V = NoL *  std::sqrt((-NoV * a2 + NoV) * NoV + a2);
    return 0.5 / (GGX_L + GGX_V);
}

inline Vector3 F_Schlick(float u, Vector3 f0){
    return f0 + (1.0f - f0) * std::pow(1.0f - u, 5.0f);
}