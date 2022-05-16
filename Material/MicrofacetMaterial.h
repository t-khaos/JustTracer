#pragma once

#include "Material.h"

enum PBRType {
    COOK_TORRANCE_GGX
};

struct MicrofacetMaterial {
    Color base_color;

    PBRType type;

    MicrofacetMaterial(Color _color, PBRType _type)
            : base_color(_color), type(_type) {}

    Vec3 Eval(const Vec3 &wi, const Vec3 &wo, const Vec3 &normal);

    double pdf(const Vec3 &wi, const Vec3 &wo);

    Vec3 Fr_COOK_TORRANCE_GGX(const Vec3 &wi, const Vec3 &wo, const Vec3 &normal);

    inline double D_GGX_TR(Vec3 N, Vec3 H, double a);

    inline double Geometry_Schlick_GGX(double NoV, double k);

    inline double GeometrySmith(Vec3 N, Vec3 V, Vec3 L, double k);

    Vec3 fresnel_schlick(double cosTheta, Vec3 F0);
};

Vec3 MicrofacetMaterial::Eval(const Vec3 &wi, const Vec3 &wo, const Vec3 &normal) {
    if (type == COOK_TORRANCE_GGX) {
        return Fr_COOK_TORRANCE_GGX(wi, wo, normal);
    }

    return Vec3(0.0);
}

Vec3 MicrofacetMaterial::Fr_COOK_TORRANCE_GGX(const Vec3 &wi, const Vec3 &wo, const Vec3 &normal) {

    double roughness = 0;
    double metallic = 0;

    Vec3 V = -wi;
    Vec3 L = wo;
    Vec3 H = (wo + wi).Normalize();
    Vec3 N = normal;

    Color diffuse_color = base_color;

    Color diffuse, specular;

    double NoV = N.Dot(V);
    double NoL = N.Dot(L);

    Vec3 F0(0.04);

    Vec3 F = fresnel_schlick(NoV, F0);
    double D = D_GGX_TR(N, H, roughness);
    double G = GeometrySmith(N, V, L, roughness);

    double c = 1.0;

    Vec3 Ks = F;
    Vec3 Kd = (Vec3(1.0) - Ks) * (Vec3(1.0) - metallic);

    diffuse = Kd * c * (1 / PI);
    specular = Ks * D * G * (1.0f / (4 * std::max(NoL, EPS) * std::max(NoV, EPS)));

    return diffuse + specular;
}

inline double MicrofacetMaterial::D_GGX_TR(Vec3 N, Vec3 H, double a) {
    double a2 = a * a;
    double NoH = std::max(N.Dot(H), 0.0);
    double NoH2 = NoH * NoH;

    double nom = a2;
    double denom = (NoH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

inline double MicrofacetMaterial::Geometry_Schlick_GGX(double NoV, double k) {
    double nom = NoV;
    double denom = NoV * (1.0 - k) + k;

    return nom / denom;
}

inline double MicrofacetMaterial::GeometrySmith(Vec3 N, Vec3 V, Vec3 L, double k) {
    double NoV = std::max(N.Dot(V), 0.0);
    double NoL = std::max(N.Dot(L), 0.0);
    double ggx1 = Geometry_Schlick_GGX(NoV, k);
    double ggx2 = Geometry_Schlick_GGX(NoL, k);

    return ggx1 * ggx2;
}

inline Vec3 MicrofacetMaterial::fresnel_schlick(double cos_theta, Vec3 F0) {
    return F0 + (Vec3(1.0) - F0) * pow(1.0 - cos_theta, 5.0);
}