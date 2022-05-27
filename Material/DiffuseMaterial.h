#pragma once

#include "../Common/Material.h"

struct DiffuseMaterial : Material {
    DiffuseMaterial(
            const Color &_c, const Color &_emi,
            const MaterialType &_type = MaterialType::DIFFUSE_IDEAL)
            : Material(_c, _emi, _type) {}


    virtual float PDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

    virtual Color EvalColor(const Vector3 &L, const Vector3 &V, const Vector3 &N)const override;

    virtual Vector3 SampleDirection(const Vector3 &L, const Vector3 &V, const Vector3 &N)const override;
};

