
#include "ReflectMaterial.h"

float ReflectMaterial::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return 1;
}

Color ReflectMaterial::EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return baseColor / Dot(N, L);
}

Vector3 ReflectMaterial::SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return SampleReflectDirection(N, V);
}
