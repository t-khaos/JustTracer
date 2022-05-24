
#include "NormalIntegrator.h"

inline Color3d NormalIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    HitResult result;
    if (scene->Intersect(ray, result)) {
        return 0.5 * (result.normal + Color3d(1.0));
    }
    double t = 0.5 * (ray.direction.y + 1.0);
    return (1.0 - t) * Color3d(1.0, 1.0, 1.0) + t * Color3d(0.5, 0.7, 1.0);
}


