#pragma once

#include "../Tool/Vector3.h"
#include "../Tool/Global.h"


enum class MaterialType{
    DIFFUSE,
    REFRACT,
};

struct Material {
    Color emission;
    Color base_color;
    MaterialType type;

    Material(const Color& _color, const MaterialType& _type)
        :base_color(_color), type(_type) {}
    virtual float PDF() = 0;
    virtual Vec3 Eval() = 0;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N)=0;
};

