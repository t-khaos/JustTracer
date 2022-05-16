#pragma once



#include "Integrator.h"


struct PathIntegrator : Integrator {
    int depth_max;
    PathIntegrator(int _depth = 5) : depth_max(_depth) {};

    virtual Color Li(const Ray &ray, Scene *scene) override;

    Color CastRay(const Ray& ray, Scene*scene, int depth);
};


Color PathIntegrator::CastRay(const Ray &ray, Scene *scene, int depth) {
    if (depth>=depth_max)
        return Color(0.0);
    HitResult result;
    if (scene->Intersect(ray, result)) {
        auto direction = result.material->Sample(ray.direction, result.normal);
        if(direction.Dot(result.normal)<0)
            return Color(0.0);
        Ray ray_out(result.point, direction);
        return result.material->Eval()*CastRay(ray_out, scene, ++depth)/result.material->PDF();
    }
    auto t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Color PathIntegrator::Li(const Ray &ray, Scene *scene) {
    return CastRay(ray, scene, 0);
}