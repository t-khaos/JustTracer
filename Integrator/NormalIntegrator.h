#pragma once

#include "Integrator.h"
#include "Material/Material.h"

struct NormalIntegrator : public Integrator {
    NormalIntegrator() {}

    virtual Color Li(const Ray &ray, std::shared_ptr<Scene> scene) override;
};

Color NormalIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    HitResult result;
    if (scene->Intersect(ray, result)) {
        return 0.5 * (result.normal + Color(1.0));
    }
    auto t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


