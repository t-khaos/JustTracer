#pragma once

#include "Material.h"


struct DiffuseMaterial : Material{
    DiffuseMaterial(
            const Color& _color,
            const MaterialType& _type = MaterialType::DIFFUSE)
            :Material(_color,_type){}

    virtual float PDF() override;
    virtual Vec3 Eval() override;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N) override;
};

float DiffuseMaterial::PDF(){
        return 1;
}
Vec3 DiffuseMaterial::Eval(){
    return base_color;
}
Vec3 DiffuseMaterial::Sample(const Vec3& V, const Vec3& N){
    double r1 = RandomDouble();
    double r2 = RandomDouble();

    double phi = 2* PI * r2;
    double z =  std::fabs(1. - 2. * r1);//[0,1]
    double radius = std::sqrt(1-z*z);//[0,1]

    double x = radius*std::cos(phi);
    double y = radius*std::sin(phi);

    Vec3 direction(x,y,z);

    return direction.ToWorld(N);
}


struct RefractMaterial : Material{
    RefractMaterial(
            const Color& _color,
            const MaterialType& _type = MaterialType::REFRACT)
            :Material(_color,_type){}

    virtual float PDF() override;
    virtual Vec3 Eval() override;
    virtual Vec3 Sample(const Vec3& V, const Vec3& N) override;

};

float RefractMaterial::PDF(){
    return 1;
}
Vec3 RefractMaterial::Eval(){
    return  base_color;
}
Vec3 RefractMaterial::Sample(const Vec3& V, const Vec3& N){
    return V.Reflect(N);
}
