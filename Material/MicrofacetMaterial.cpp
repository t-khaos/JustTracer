/*

#include "Material.h"

enum PBRType {
    COOK_TORRANCE_GGX
};

struct MicrofacetMaterial {
    Color3d baseColor;

    PBRType type;

    MicrofacetMaterial(Color3d _color, PBRType _type)
            : baseColor(_color), type(_type) {}

    Vector3d Eval(const Vector3d &wi, const Vector3d &wo, const Vector3d &normal);

    double pdf(const Vector3d &wi, const Vector3d &wo);

    Vector3d Fr_COOK_TORRANCE_GGX(const Vector3d &wi, const Vector3d &wo, const Vector3d &normal);

    double D_GGX_TR(Vector3d N, Vector3d H, double a);

    double Geometry_Schlick_GGX(double NoV, double k);

    double GeometrySmith(Vector3d N, Vector3d V, Vector3d L, double k);

    Vector3d fresnel_schlick(double cosTheta, Vector3d F0);
};

Vector3d MicrofacetMaterial::EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &normal) {
    if (type == COOK_TORRANCE_GGX) {
        return Fr_COOK_TORRANCE_GGX(wi, wo, normal);
    }

    return Vector3d(0.0);
}

Vector3d MicrofacetMaterial::Fr_COOK_TORRANCE_GGX(const Vector3d &wi, const Vector3d &wo, const Vector3d &normal) {

    double roughness = 0;
    double metallic = 0;

    Vector3d V = -wi;
    Vector3d L = wo;
    Vector3d H = (wo + wi).Normalize();
    Vector3d N = normal;

    Color3d diffuse_color = baseColor;

    Color3d diffuse, specular;

    double NoV = N.Dot(V);
    double NoL = N.Dot(L);

    Vector3d F0(0.04);

    Vector3d F = fresnel_schlick(NoV, F0);
    double D = D_GGX_TR(N, H, roughness);
    double G = GeometrySmith(N, V, L, roughness);

    double c = 1.0;

    Vector3d Ks = F;
    Vector3d Kd = (Vector3d(1.0) - Ks) * (Vector3d(1.0) - metallic);

    diffuse = Kd * c * (1 / PI);
    specular = Ks * D * G * (1.0f / (4 * std::max(NoL, EPSILON) * std::max(NoV, EPSILON)));

    return diffuse + specular;
}

double MicrofacetMaterial::D_GGX_TR(Vector3d N, Vector3d H, double a) {
    double a2 = a * a;
    double NoH = std::max(N.Dot(H), 0.0);
    double NoH2 = NoH * NoH;

    double nom = a2;
    double denom = (NoH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

double MicrofacetMaterial::Geometry_Schlick_GGX(double NoV, double k) {
    double nom = NoV;
    double denom = NoV * (1.0 - k) + k;

    return nom / denom;
}

double MicrofacetMaterial::GeometrySmith(Vector3d N, Vector3d V, Vector3d L, double k) {
    double NoV = std::max(N.Dot(V), 0.0);
    double NoL = std::max(N.Dot(L), 0.0);
    double ggx1 = Geometry_Schlick_GGX(NoV, k);
    double ggx2 = Geometry_Schlick_GGX(NoL, k);

    return ggx1 * ggx2;
}

Vector3d MicrofacetMaterial::fresnel_schlick(double cos_theta, Vector3d F0) {
    return F0 + (Vector3d(1.0) - F0) * pow(1.0 - cos_theta, 5.0);
}
*/
