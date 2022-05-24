#pragma once

#include "PathIntegrator.h"

struct SimplePathIntegrator : PathIntegrator {

    SimplePathIntegrator(int _depth = 5) : PathIntegrator(_depth) {}

    virtual Color3d Li(const Ray &ray, std::shared_ptr<World> scene) override;

    virtual Color3d CastRay(const Ray &ray, std::shared_ptr<World> scene, int depth) override;
};
