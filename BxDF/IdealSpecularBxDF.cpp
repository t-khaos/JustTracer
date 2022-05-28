
#include "IdealSpecularBxDF.h"

float IdealSpecularBxDF::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return 1;
}

Color IdealSpecularBxDF::Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return albedo / Dot(N, L);
}

BxDFResult IdealSpecularBxDF::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 direction = SpecularDirection(N, V);
    float pdf = PDF(direction, V, N);
    Color fr = Eval(direction, V, N);
    return BxDFResult(direction, pdf, fr, true);
}
