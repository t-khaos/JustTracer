#pragma once

#include "../Renderer/Integrator.h"

struct MonteCarloPathIntegrator : PathIntegrator {

    float P_RR = 0.8;
    HitResult firstHitResult;

    MonteCarloPathIntegrator(int _depth = 5) : PathIntegrator(_depth) {}

    virtual Color Li(const Ray &ray, std::shared_ptr<Scene> scene) override;

    virtual Color CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) override;
};