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

inline Vector3 SampleDiffuseDirection(const Vector3& normal){
    float phi = 2 * PI * RandomFloat();
    float z = std::fabs(1.0f - 2 * RandomFloat());//[0,1]
    float radius = std::sqrt(1.0f - z * z);//[0,1]

    float x = radius * std::cos(phi);
    float y = radius * std::sin(phi);

    Vector3 direction(x, y, z);

    return ToWorld(direction, normal);
}

inline Vector3 SampleReflectDirection(const Vector3& N, const Vector3& V){
    return (-V) - 2 * Dot((-V) , N) * N;
}