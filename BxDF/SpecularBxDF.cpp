
#include "SpecularBxDF.h"

float SpecularBxDF::PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return 1;
}

Color SpecularBxDF::Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    return albedo / Dot(N, L);
}

BxDFResult SpecularBxDF::SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const {
    Vector3 direction = SpecularDirection(N, V);
    float pdf = PDF(L, V, N);
    Color fr = Eval(L, V, N);
    return BxDFResult(direction, pdf, fr, true);
}