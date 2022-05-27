#pragma once

#include "../Common/Material.h"

struct DiffuseMaterial : Material {
    DiffuseMaterial(
            const Color &_color,
            const Color &_emission,
            const MaterialType &_type = MaterialType::DIFFUSE_IDEAL)
            : Material(_color, _emission, _type) {}


    virtual float PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const override;

    virtual Color EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &N)const override;

    virtual Vector3 SampleDirection(const Vector3 &wi, const Vector3 &N)const override;
};

