#pragma once

#include <algorithm>
#include "../Common/Material.h"


struct MicrofacetMaterial : Material {

    float roughness = 0;
    float metallic = 0;
    float reflectance = 0;

    MicrofacetMaterial(
            float _rou, float _met, float _ref,
            const Color &_c, const Color &_emi,
            const MaterialType &_type = MaterialType::MIRCOFACET)
            : Material(_c, _emi, _type), roughness(_rou), metallic(_met), reflectance(_ref) {

    }

    virtual BxDFResult SampleBxDF(const Vector3 &L, const Vector3 &V, const Vector3 &N) const override;

};
