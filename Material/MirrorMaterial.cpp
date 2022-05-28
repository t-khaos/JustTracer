
#include "MirrorMaterial.h"
#include "../BxDF/IdealSpecularBxDF.h"

BxDFResult MirrorMaterial::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const{
    IdealSpecularBxDF bxdf(baseColor);
    return bxdf.SampleBxDF(L,V,N);
}
