#pragma once

#include "DiffuseMaterial.h"
#include "../Math/Random.h"


float DiffuseMaterial::PDF(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const {
    float NoL = Dot(wi, N);
    //理想漫反射材质，采样方向在法线附近集中，对cos_theta_o重要性采样，收敛更快
    if(type == MaterialType::DIFFUSE_IDEAL)
        return NoL / PI;

    return 0.5f / PI;
}


Color DiffuseMaterial::EvalColor(const Vector3 &wi, const Vector3 &wo, const Vector3 &N) const{
    return baseColor / PI;
}

Vector3 DiffuseMaterial::SampleDirection(const Vector3 &wi, const Vector3 &N)const {
    float phi = 2 * PI * RandomFloat();
    float z = std::fabs(1.0f - 2 * RandomFloat());//[0,1]
    float radius = std::sqrt(1.0f - z * z);//[0,1]

    float x = radius * std::cos(phi);
    float y = radius * std::sin(phi);

    Vector3 direction(x, y, z);

    return ToWorld(direction, N);
}