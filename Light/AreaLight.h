#pragma once

#include "Light.h"


struct AreaLight : Light {

/*    std::shared_ptr<Triangle> triangle;
    AreaLight(const std::shared_ptr<Triangle> &_triangle) : triangle(_triangle) {}*/

    std::shared_ptr<Rectangle> rectangle;

    AreaLight(const std::shared_ptr<Rectangle> &_rec) : rectangle(_rec) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;
};

inline void AreaLight::Sample(HitResult &result) {
    //矩形内均匀采样
    result.point = rectangle->A + rectangle->s * RandomFloat() + rectangle->t * RandomFloat();
    result.material = rectangle->material;
    result.normal = rectangle->normal;
}


inline float AreaLight::PDF() {
    return 1 / rectangle->area;
}

/*inline void AreaLight::Sample(HitResult &result) {
    //随机选取 mesh 中的一个三角形
    int index = static_cast<int>(RandomFloat()+0.5f);//[0.5,1.5]四舍五入
    auto triangle = mesh->triangles[index];

    //三角形内均匀采样
    //α = 1 - √u, β = √u * v, γ = √u * (1 - √v)
    //可以优化为
    //设 s = √u, 有 α = 1 - s, β = s * v, γ = 1 - α - β

    float s = std::sqrtf(RandomFloat());
    float v = RandomFloat();
    float alpha = 1 - s;
    float beta = s * v;

    result.point =
            alpha * triangle->A
            + beta * triangle->B
            + (1 - alpha - beta) * triangle->C;

    result.material = mesh->material;
    result.normal = triangle->normal;
}*/