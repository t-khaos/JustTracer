#pragma once

#include "../Math/Global.h"
#include "../Math/Vector.h"

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

    Material(const Color &_color, const Color &_emission, const MaterialType &_type)
            : baseColor(_color), emission(_emission), type(_type) {}

    virtual float PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const = 0;

    virtual Color EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &N)const = 0;

    virtual Vector3 SampleDirection(const Vector3 &wi, const Vector3 &N)const = 0;
};