/*
#pragma once

#include "../Common/Material.h"

struct ReflectMaterial : Material {
    ReflectMaterial(
            const Color3d &_color,
            const Color3d &_emission,
            const MaterialType &_type = MaterialType::REFRACT)
            : Material(_color, _emission, _type) {}

    virtual double PDF(const double& NoL) const override;

    virtual Vector3d EvalColor(const double& NoL) const  override;

    virtual Vector3d SampleDirection(const Vector3d &V, const Vector3d &N) const override;

};*/
