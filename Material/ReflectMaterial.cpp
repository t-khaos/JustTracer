
#include "ReflectMaterial.h"

double ReflectMaterial::PDF(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) const {
    return 1;
}

Color3d ReflectMaterial::EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) const {
    return baseColor / Dot(wo, N);
}

Vector3d ReflectMaterial::SampleDirection(const Vector3d &wi, const Vector3d &N) const {
    return Reflect(wi, N);
}
