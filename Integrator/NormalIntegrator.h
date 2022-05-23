#pragma once

#include "IIntegrator.h"

struct NormalIntegrator : public IIntegrator {
    NormalIntegrator() {}

    virtual Color3f Li(const Ray &ray, std::shared_ptr<Scene> scene) override;
};

inline Color3f NormalIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    HitResult result;
    if (scene->Intersect(ray, result, MAX_FLOAT)) {
        return 0.5f * (result.normal + Color3f(1.f));
    }
    float t = 0.5f * (ray.direction.y + 1.0);
    return (1.0f - t) * Color3f(1.f, 1.f, 1.f) + t * Color3f(0.5f, 0.7f, 1.f);
}


