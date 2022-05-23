

#include "../Common/Material.h"

struct DiffuseMaterial : Material {
    DiffuseMaterial(
            const Color3f &_color,
            const Color3f &_emission,
            const MaterialType &_type = MaterialType::DIFFUSE)
            : Material(_color, _emission, _type) {}


    virtual float PDF(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f Eval(const Vector3f &wi, const Vector3f &wo, const Vector3f &N) override;

    virtual Vector3f SampleDirection(const Vector3f &V, const Vector3f &N) override;
};

