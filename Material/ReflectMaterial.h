#pragma once

#include "../Common/Material.h"

struct ReflectMaterial : Material {
    ReflectMaterial(
            const Color &_color,
            const Color &_emission,
            const MaterialType &_type = MaterialType::REFLECT)
            : Material(_color, _emission, _type) {}

    virtual float PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const override;

    virtual Color EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const  override;

    virtual Vector3 SampleDirection(const Vector3 &wi, const Vector3 &N) const override;

};
