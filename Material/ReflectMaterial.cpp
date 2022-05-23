
#include "ReflectMaterial.h"

float ReflectMaterial::PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    return 1;
}

Vector3f ReflectMaterial::Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) {
    return base_color;
}

Vector3f ReflectMaterial::SampleDirection(const Vector3f &V, const Vector3f &N) {
    return Reflect(V, N);
}