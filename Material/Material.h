#pragma once

#include "../Tool/Vector3.h"
#include "../Tool/Global.h"


enum class MaterialType{
    DIFFUSE,
    REFRACT,
    LIGHT,
};

struct Material {
    Color emission;
    Color base_color;
    MaterialType type;

    Material(const Color& _color, const Color& _emission, const MaterialType& _type)
        :base_color(_color),emission(_emission), type(_type) {}
    virtual float PDF(const Vec3& wi, const Vec3& wo, const Vec3& N) = 0;
    virtual Vec3 Eval(const Vec3& wi, const Vec3& wo, const Vec3& N) = 0;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N)=0;
};

