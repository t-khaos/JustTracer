
#include "MicrofacetMaterial.h"
#include "../BxDF/IdealDiffuseBxDF.h"
#include "../BxDF/MicrofacetSpecularBxDF.h"
#include "../Math/Math.h"

BxDFResult MicrofacetMaterial::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const{
    IdealDiffuseBxDF diffuseBxDf(baseColor);
    MicrofacetSpecularBxDF specularBxDF(roughness, metallic, reflectance, baseColor);
    Vector3 H = Normalize(L+V);
    Vector3 F = FresnelSchlick(Dot(V,H), specularBxDF.F0());
    float probability = ToGrayScale(F);
    return probability<RandomFloat() ? specularBxDF.SampleBxDF(L, V, N) : diffuseBxDf.SampleBxDF(L, V, N);
}


