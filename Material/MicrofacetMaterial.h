/*
#pragma once

#include "Material.h"

enum PBRType {
    COOK_TORRANCE_GGX
};

struct MicrofacetMaterial {
    Color3f base_color;

    PBRType type;

    MicrofacetMaterial(Color3f _color, PBRType _type)
            : base_color(_color), type(_type) {}

    Vector3f Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &normal);

    float pdf(const Vector3f &wi, const Vector3f &wo);

    Vector3f Fr_COOK_TORRANCE_GGX(const Vector3f &wi, const Vector3f &wo, const Vector3f &normal);

    inline float D_GGX_TR(Vector3f N, Vector3f H, float a);

    inline float Geometry_Schlick_GGX(float NoV, float k);

    inline float GeometrySmith(Vector3f N, Vector3f V, Vector3f L, float k);

    Vector3f fresnel_schlick(float cosTheta, Vector3f F0);
};

Vector3f MicrofacetMaterial::Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &normal) {
    if (type == COOK_TORRANCE_GGX) {
        return Fr_COOK_TORRANCE_GGX(wi, wo, normal);
    }

    return Vector3f(0.0);
}

Vector3f MicrofacetMaterial::Fr_COOK_TORRANCE_GGX(const Vector3f &wi, const Vector3f &wo, const Vector3f &normal) {

    float roughness = 0;
    float metallic = 0;

    Vector3f V = -wi;
    Vector3f L = wo;
    Vector3f H = (wo + wi).Normalize();
    Vector3f N = normal;

    Color3f diffuse_color = base_color;

    Color3f diffuse, specular;

    float NoV = N.Dot(V);
    float NoL = N.Dot(L);

    Vector3f F0(0.04);

    Vector3f F = fresnel_schlick(NoV, F0);
    float D = D_GGX_TR(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);

    float c = 1.0;

    Vector3f Ks = F;
    Vector3f Kd = (Vector3f(1.0) - Ks) * (Vector3f(1.0) - metallic);

    diffuse = Kd * c * (1 / PI);
    specular = Ks * D * G * (1.0f / (4 * std::max(NoL, EPSILON) * std::max(NoV, EPSILON)));

    return diffuse + specular;
}

inline float MicrofacetMaterial::D_GGX_TR(Vector3f N, Vector3f H, float a) {
    float a2 = a * a;
    float NoH = std::max(N.Dot(H), 0.0);
    float NoH2 = NoH * NoH;

    float nom = a2;
    float denom = (NoH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

inline float MicrofacetMaterial::Geometry_Schlick_GGX(float NoV, float k) {
    float nom = NoV;
    float denom = NoV * (1.0 - k) + k;

    return nom / denom;
}

inline float MicrofacetMaterial::GeometrySmith(Vector3f N, Vector3f V, Vector3f L, float k) {
    float NoV = std::max(N.Dot(V), 0.0);
    float NoL = std::max(N.Dot(L), 0.0);
    float ggx1 = Geometry_Schlick_GGX(NoV, k);
    float ggx2 = Geometry_Schlick_GGX(NoL, k);

    return ggx1 * ggx2;
}

inline Vector3f MicrofacetMaterial::fresnel_schlick(float cos_theta, Vector3f F0) {
    return F0 + (Vector3f(1.0) - F0) * pow(1.0 - cos_theta, 5.0);
}
*/
