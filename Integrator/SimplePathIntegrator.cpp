
#include "SimplePathIntegrator.h"

Color3d SimplePathIntegrator::Li(const Ray &ray, std::shared_ptr<World> scene) {
    return CastRay(ray, scene, 0);
}

Color3d SimplePathIntegrator::CastRay(const Ray &ray, std::shared_ptr<World> scene, int depth) {
    if (depth >= depth_max)
        return Color3d(0.0);
    HitResult result;
    if (scene->Intersect(ray, result)) {
        if (result.material->type == MaterialType::LIGHT)
            return result.material->emission;
        auto direction = result.material->SampleDirection(ray.direction, result.normal);
        if (Dot(direction, result.normal) < 0)
            return Color3d(0.0);
        Ray ray_out(result.point, direction);
        return
                result.material->EvalColor(ray.direction, direction, result.normal)
                * CastRay(ray_out, scene, ++depth)
                / result.material->PDF(ray.direction, direction, result.normal);
    }
    return Color3d(0.0);
    /*auto t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color3d(1.0, 1.0, 1.0) + t * Color3d(0.5, 0.7, 1.0);*/
}

