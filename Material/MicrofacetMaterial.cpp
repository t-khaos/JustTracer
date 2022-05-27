


#include <algorithm>
#include "../Common/Material.h"


struct MicrofacetMaterial : Material {

    MicrofacetMaterial(const Color3d &_color,
                       const Color3d &_emission,
                       const MaterialType &_type = MaterialType::MICROFACET)
            : Material(_color, _emission, _type) {}

    virtual double PDF(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) const override;

    virtual Color3d EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N)const override;

    virtual Vector3d SampleDirection(const Vector3d &wi, const Vector3d &N)const override;


    double D_GGX_TR(Vector3d N, Vector3d H, double a)const;

    double Geometry_Schlick_GGX(double NoV, double k)const;

    double GeometrySmith(Vector3d N, Vector3d V, Vector3d L, double k)const;

    Vector3d fresnel_schlick(double cosTheta, Vector3d F0)const;
};

Color3d MicrofacetMaterial::EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N)const {
    double roughness = 0;
    double metallic = 0;

    Vector3d V = -wi;
    Vector3d L = wo;
    Vector3d H = Normalize(wo + wi);

    Color3d diffuse_color = baseColor;

    Color3d diffuse, specular;

    double NoV = Dot(N,V);
    double NoL = Dot(N,L);

    Vector3d F0(0.04);

    Vector3d F = fresnel_schlick(NoV, F0);
    double D = D_GGX_TR(N, H, roughness);
    double G = GeometrySmith(N, V, L, roughness);

    double c = 1.0;

    Vector3d Ks = F;
    Vector3d Kd = (Vector3d(1.0) - Ks) * (1.0 - metallic);

    diffuse = Kd * c * (1 / PI);
    specular = Ks * D * G * (1.0f / (4 * std::max(NoL, EPSILON) * std::max(NoV, EPSILON)));

    return diffuse + specular;
}

double MicrofacetMaterial::D_GGX_TR(Vector3d N, Vector3d H, double a) const{
    double a2 = a * a;
    double NoH = std::max(Dot(N,H), 0.0);
    double NoH2 = NoH * NoH;

    double nom = a2;
    double denom = (NoH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

double MicrofacetMaterial::Geometry_Schlick_GGX(double NoV, double k)const {
    double nom = NoV;
    double denom = NoV * (1.0 - k) + k;

    return nom / denom;
}

double MicrofacetMaterial::GeometrySmith(Vector3d N, Vector3d V, Vector3d L, double k) const{
    double NoV = std::max(Dot(N,V), 0.0);
    double NoL = std::max(Dot(N,L), 0.0);
    double ggx1 = Geometry_Schlick_GGX(NoV, k);
    double ggx2 = Geometry_Schlick_GGX(NoL, k);

    return ggx1 * ggx2;
}

Vector3d MicrofacetMaterial::fresnel_schlick(double cos_theta, Vector3d F0) const{
    return F0 + (Vector3d(1.0) - F0) * pow(1.0 - cos_theta, 5.0);
}
