#pragma once



#include "PathIntegrator.h"



struct SimplePathIntegrator : PathIntegrator {

    SimplePathIntegrator(int _depth = 5): PathIntegrator(_depth){}

    virtual Color Li(const Ray &ray, std::shared_ptr<Scene> scene) override;

    virtual Color CastRay(const Ray& ray, std::shared_ptr<Scene> scene, int depth) override;
};

Color SimplePathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}
Color SimplePathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    if (depth>=depth_max)
        return {0};
    HitResult result;
    if (scene->Intersect(ray, result)) {
        if(result.material->type==MaterialType::LIGHT)
            return result.material->emission;
        auto direction = result.material->Sample(ray.direction, result.normal);
        if(direction.Dot(result.normal)<0)
            return Color(0.0);
        Ray ray_out(result.point, direction);
        return
            result.material->Eval(ray.direction,direction,result.normal)
            *CastRay(ray_out, scene, ++depth)
            /result.material->PDF(ray.direction,direction,result.normal);
    }
    return {0};
    /*auto t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);*/
}

