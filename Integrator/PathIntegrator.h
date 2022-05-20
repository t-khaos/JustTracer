#pragma once



#include "Integrator.h"

struct PathIntegrator:Integrator{
    int depth_max;
    PathIntegrator(int _depth = 5):depth_max(_depth){}
    virtual Color Li(const Ray &ray, std::shared_ptr<Scene> scene) = 0;
    virtual Color CastRay(const Ray& ray, std::shared_ptr<Scene> scene, int depth) = 0;
};