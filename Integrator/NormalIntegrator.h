#pragma once

#include "../Common/Integrator.h"

struct NormalIntegrator : Integrator {
    NormalIntegrator() {}

    virtual Color3d Li(const Ray &ray, std::shared_ptr<Scene> scene) override;
};