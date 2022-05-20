#pragma once

#include "Material.h"


struct DiffuseMaterial : Material{
    DiffuseMaterial(
            const Color& _color,
            const Color& _emission,
            const MaterialType& _type = MaterialType::DIFFUSE)
            :Material(_color,_emission, _type){}


    virtual float PDF(const Vec3& wi, const Vec3& wo, const Vec3& N) override;
    virtual Vec3 Eval(const Vec3& wi, const Vec3& wo, const Vec3& N) override;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N) override;
};

float DiffuseMaterial::PDF(const Vec3& wi, const Vec3& wo, const Vec3& N){
    if(wo.Dot(N)>0.0)
        return 0.5/PI;
    else
        return 0.0;
}
Vec3 DiffuseMaterial::Eval(const Vec3& wi, const Vec3& wo, const Vec3& N){
    if(wo.Dot(N)>0.0)
        return base_color/PI;
    else
        return {0};
}
Vec3 DiffuseMaterial::Sample(const Vec3& V, const Vec3& N){
    float phi = 2* PI * RandomFloat();
    float z =  std::fabs(1. - 2. * RandomFloat());//[0,1]
    float radius = std::sqrt(1-z*z);//[0,1]

    float x = radius*std::cos(phi);
    float y = radius*std::sin(phi);

    Vec3 direction(x,y,z);

    return direction.ToWorld(N);
}
