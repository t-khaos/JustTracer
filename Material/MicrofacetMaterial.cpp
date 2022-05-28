
#include "MicrofacetMaterial.h"
#include "../BxDF/MicrofacetBxDF.h"

BxDFResult MicrofacetMaterial::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const{
    MicrofacetBxDF bxdf(roughness, metallic, reflectance, baseColor);
    return bxdf.SampleBxDF(L, V, N);
}


