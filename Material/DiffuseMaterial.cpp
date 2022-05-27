#pragma once

#include "DiffuseMaterial.h"


float DiffuseMaterial::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return Dot(N, L) / PI;
}


Color DiffuseMaterial::EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N) const{
    return baseColor / PI;
}

Vector3 DiffuseMaterial::SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &N)const {
    return SampleDiffuseDirection(N);
}