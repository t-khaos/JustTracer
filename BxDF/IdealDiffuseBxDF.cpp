
#include "IdealDiffuseBxDF.h"

float IdealDiffuseBxDF::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return Dot(N, L) / PI;
}

Color IdealDiffuseBxDF::Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return albedo / PI;
}

BxDFResult IdealDiffuseBxDF::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 direction = DiffuseDirection(N);
    float pdf = PDF(direction, V, N);
    Color fr = Eval(direction, V, N);
    return BxDFResult(direction, pdf, fr, false);
}
