#pragma once

#include "Light.h"

struct AreaLight : Light {
    std::shared_ptr<Triangle> triangle;

    AreaLight(const std::shared_ptr<Triangle> &_triangle) : triangle(_triangle) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;
};

inline void AreaLight::Sample(HitResult &result) {

    //三角形内均匀采样
    //α = 1 - √u, β = √u * v, γ = √u * (1 - √v)
    //可以优化为
    //设 s = √u, 有 α = 1 - s, β = s * v, γ = 1 - α - β

    //随机选取一个三角形

    float s = std::sqrtf(RandomFloat());
    float v = RandomFloat();
    float alpha = 1 - s;
    float beta = s * v;

    result.point =
            alpha * triangle->A
            + beta * triangle->B
            + (1 - alpha - beta) * triangle->C;

    result.material = triangle->material;
    result.normal = triangle->normal;
}

inline float AreaLight::PDF() {
    return 1 / triangle->area;
}