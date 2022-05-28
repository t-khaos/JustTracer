#pragma once

#include "../Common/BxDF.h"

struct SpecularBxDF : BxDF {

    SpecularBxDF(const Color &_albedo) : BxDF(_albedo) {}

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Color Eval(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;
};