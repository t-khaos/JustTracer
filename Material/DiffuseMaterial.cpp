#pragma once

#include "DiffuseMaterial.h"
#include "../Math/Random.h"


double DiffuseMaterial::PDF(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) {
    double NoL = Dot(wo, N) ;

    if (NoL < 0.0)
        return 0.0;

    //理想漫反射材质，采样方向在法线附近集中，对cos_theta_o重要性采样，收敛更快
    if(type == MaterialType::DIFFUSE_IDEAL)
        return NoL / PI;

    return 0.5 / PI;
}


Color3d DiffuseMaterial::EvalColor(const Vector3d &wi, const Vector3d &wo, const Vector3d &N) {
    double NoL = Dot(wo, N) ;

    if (NoL < 0.0)
        return 0.0;

    return baseColor / PI;
}

Vector3d DiffuseMaterial::SampleDirection(const Vector3d &V, const Vector3d &N) {
    double phi = 2 * PI * RandomDouble();
    double z = std::fabs(1.0 - 2 * RandomDouble());//[0,1]
    double radius = std::sqrt(1 - z * z);//[0,1]

    double x = radius * std::cos(phi);
    double y = radius * std::sin(phi);

    Vector3d direction(x, y, z);

    return ToWorld(direction, N);
}