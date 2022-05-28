#pragma once

#include "DiffuseMaterial.h"
#include "../BxDF/IdealDiffuseBxDF.h"


BxDFResult DiffuseMaterial::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const{
    IdealDiffuseBxDF bxdf(baseColor);
    return bxdf.SampleBxDF(L,V,N);
}