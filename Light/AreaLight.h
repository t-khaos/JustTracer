#pragma once

#include "Light.h"

struct AreaLight : Light {
    std::vector<std::shared_ptr<Triangle>> triangles;

    AreaLight(const std::vector<std::shared_ptr<Triangle>> &_triangles) : triangles(_triangles) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;
};

void AreaLight::Sample(HitResult &result) {

    //三角形内均匀采样
    //α = 1 - √u, β = √u * v, γ = √u * (1 - √v)
    //可以优化为
    //设 s = √u, 有 α = 1 - s, β = s * v, γ = 1 - α - β

    int index = RandomFloat(0, triangles.size());
    auto triangle = triangles[index];
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

float AreaLight::PDF() {
    float totalArea = 0.f;
    for (auto triangle: triangles)
        totalArea += triangle->area;
    return 1 / totalArea;
}