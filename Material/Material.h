#pragma once

#include "../Tool/Vector3.h"
#include "../Tool/Global.h"


struct Material {
    Color emission;
    Color base_color;

    Material() {}
    virtual float PDF(const Vec3 &L, const Vec3 &V, const Vec3 &N);
    virtual Vec3 Eval(const Vec3 &L, const Vec3 &V, const Vec3 &N) = 0;
    virtual Vec3 Sample();
};

struct DiffuseMaterial : Material{
    virtual float PDF(const Vec3 &L, const Vec3 &V, const Vec3 &N) override;
    virtual Vec3 Eval(const Vec3 &L, const Vec3 &V, const Vec3 &N) override;
    virtual Vec3 Sample() override;
};

float DiffuseMaterial::PDF(const Vec3 &L, const Vec3 &V, const Vec3 &N){
    double NoV = N.dot(V);
    if(NoV > EPS)
        return 0.5f/PI;
    else
        return 0.0f;
}
Vec3 DiffuseMaterial::Eval(const Vec3 &L, const Vec3 &V, const Vec3 &N){
    double NoV = N.dot(V);
    if(NoV > EPS){
        Color diffuse_color = base_color / PI;
        return diffuse_color;
    }
    else
        return Color(0.0);
}
Vec3 DiffuseMaterial::Sample(){
    double r1 = RandomDouble();
    double r2 = RandomDouble();

    //TODO
    //极坐标
    double phi = 2* PI * r2;

    return Vec3();
}
