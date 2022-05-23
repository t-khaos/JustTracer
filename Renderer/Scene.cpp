
#include "Scene.h"


bool Scene::Intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    float closestTime = MAX_FLOAT;

    for (auto &object: objects) {
        if (object->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = tempResult.distance;
            result = tempResult;
        }
    }
    return isHit;
}