
#include "Scene.h"


bool Scene::Intersect(Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    float closestTime = MAX_FLOAT;

    size_t index = 0;
    for (auto &object: objects) {
        if (object->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = tempResult.time;
            result = tempResult;
            ray.distance = tempResult.time;
            ray.objIndex = index;
        }
        index++;
    }
    return isHit;
}

void Scene::SampleLight(LightResult &result) const{
    auto light = lights[0];
    return light->SampleLight(result);
}