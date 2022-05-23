#pragma once

#include "PathIntegrator.h"

struct MonteCarloPathIntegrator : PathIntegrator {
    float P_RR = 0.8;

    MonteCarloPathIntegrator(int _depth = 5) : PathIntegrator(_depth) {}

    virtual Color3f Li(const Ray &ray, std::shared_ptr<Scene> scene) override;

    virtual Color3f CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) override;
};