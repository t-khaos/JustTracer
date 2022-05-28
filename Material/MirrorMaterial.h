#pragma once

#include "../Common/Material.h"

struct MirrorMaterial : Material {
    MirrorMaterial(
            const Color &_c, const Color &_emi,
            MaterialType _type)
            : Material(_c, _emi, _type) {}

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

};
