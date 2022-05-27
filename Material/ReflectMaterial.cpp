
#include "ReflectMaterial.h"

float ReflectMaterial::PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const {
    return 1;
}

Color ReflectMaterial::EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const {
    return baseColor / Dot(wo, N);
}

Vector3 ReflectMaterial::SampleDirection(const Vector3 &wi, const Vector3 &N) const {
    return Reflect(wi, N);
}
