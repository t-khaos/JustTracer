#pragma once

#include "../Math/Global.h"
#include "../Math/Vector.h"
#include "../Math/Random.h"
#include "BxDFResult.h"

enum class MaterialType {
    DIFFUSE,
    DIFFUSE_IDEAL,
    DIFFUSE_IDEAL_REMAP,
    REFLECT,
    LIGHT,
    MICROFACET
};

struct Material {
    Color emission;
    Color baseColor;
    MaterialType type;

    Material(const Color &_c, const Color &_emi, const MaterialType &_type)
            : baseColor(_c), emission(_emi), type(_type) {}

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const = 0;
};