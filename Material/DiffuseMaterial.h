

#include "../Common/Material.h"

struct DiffuseMaterial : Material {
    DiffuseMaterial(
            const Color3d &_color,
            const Color3d &_emission,
            const MaterialType &_type = MaterialType::DIFFUSE_IDEAL)
            : Material(_color, _emission, _type) {}


    virtual double PDF(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) override;

    virtual Vector3d EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) override;

    virtual Vector3d SampleDirection(const Vector3d &V, const Vector3d &N) override;
};

