#pragma once

#include "Material.h"

struct RefractMaterial : Material{
    RefractMaterial(
            const Color& _color,
            const Color& _emission,
            const MaterialType& _type = MaterialType::REFRACT)
            :Material(_color, _emission , _type){}

    virtual float PDF(const Vec3& wi, const Vec3& wo, const Vec3& N) override;
    virtual Vec3 Eval(const Vec3& wi, const Vec3& wo, const Vec3& N) override;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N) override;

};

float RefractMaterial::PDF(const Vec3& wi, const Vec3& wo, const Vec3& N){
    return 1;
}
Vec3 RefractMaterial::Eval(const Vec3& wi, const Vec3& wo, const Vec3& N){
    return  base_color;
}
Vec3 RefractMaterial::Sample(const Vec3& V, const Vec3& N){
    return V.Reflect(N);
}