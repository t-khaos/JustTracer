
#include "MicrofacetMaterial.h"

float MicrofacetMaterial::PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const {
    Vector3 v = -wo;
    Vector3 l = wi;
    Vector3 h = Normalize(v + l);

    float roughness = perceptualRoughness * perceptualRoughness;
    float NoH = std::clamp(Dot(N, h), 0.0f, 1.0f);
    float D = D_GGX(NoH, roughness);

    return NoH*D;
}

Vector3 MicrofacetMaterial::SampleDirection(const Vector3 &wi, const Vector3 &N) const {
    return Vector3(1.0f);
}

Color MicrofacetMaterial::EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &normal) const {
    /* ==================================================================== */
    /*                         Filament PBR Document                        */
    /* ==================================================================== */

    //—————————————————
    //   wi   n    wo
    //   ↘    ↑    ↗
    //—————————————————
    //   v    n    l
    //   ↖    ↑    ↗
    //—————————————————

    Vector3 v = -wo;
    Vector3 l = wi;
    Vector3 h = Normalize(v + l);

    //粗糙度重映射
    float roughness = perceptualRoughness * perceptualRoughness;

    //漫反射颜色
    Color diffuseColor = (1 - metallic) * baseColor;
    //统一电解质和金属材质的掠射角f0
    //注：加法前项为常量，后项为矢量，加法操作符重载会将前项转为各维数值相同的矢量进行运算
    Color f0 = 0.16f * reflectance * reflectance * (1-metallic) + baseColor * metallic;

    //入射和出射方向与法线的夹角余弦
    float NoV = std::abs(Dot(normal, v)) + 1e-5;
    float NoL = std::clamp(Dot(normal, l), 0.0f, 1.0f);
    float NoH = std::clamp(Dot(normal, h), 0.0f, 1.0f);
    float LoH = std::clamp(Dot(l, h), 0.0f, 1.0f);

    float D = D_GGX(NoH, roughness);
    Color F = F_Schlick(LoH, f0);
    float V = V_SmithGGXCorrelated(NoV, NoL, roughness);

    Color Fr = D * V * F;
    Color Fd = diffuseColor * (1/PI);

    return Fr + Fd;
}


