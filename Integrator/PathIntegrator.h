
#include "../Common/Integrator.h"

struct PathIntegrator : Integrator {
    int depth_max;

    PathIntegrator(int _depth = 5) : depth_max(_depth) {}

    virtual Color3d Li(const Ray &ray, std::shared_ptr<World> scene) = 0;

    virtual Color3d CastRay(const Ray &ray, std::shared_ptr<World> scene, int depth) = 0;
};

