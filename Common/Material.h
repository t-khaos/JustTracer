#pragma once

#include "Global.h"
#include "../Math/Vector.h"

enum class MaterialType {
    DIFFUSE,
    DIFFUSE_IDEAL,
    REFRACT,
    LIGHT,
};

struct Material {
    Color3d emission;
    Color3d baseColor;
    MaterialType type;

    Material(const Color3d &_color, const Color3d &_emission, const MaterialType &_type)
            : baseColor(_color), emission(_emission), type(_type) {}

    virtual double PDF(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) = 0;

    virtual Color3d EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) = 0;

    virtual Vector3d SampleDirection(const Vector3d &V, const Vector3d &N) = 0;
};