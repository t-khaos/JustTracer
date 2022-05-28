#pragma once

#include "../Math/Global.h"
#include "../Math/Vector.h"
#include "../Math/Random.h"

enum class MaterialType {
    DIFFUSE,
    DIFFUSE_IDEAL,
    DIFFUSE_IDEAL_REMAP,
    REFLECT,
    LIGHT,
    MIRCOFACET
};

struct Material {
    Color emission;
    Color baseColor;
    MaterialType type;

    Material(const Color &_c, const Color &_emi, const MaterialType &_type)
            : baseColor(_c), emission(_emi), type(_type) {}

    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const = 0;

    virtual Color EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N)const = 0;

    virtual Vector3 SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &normal)const = 0;
};