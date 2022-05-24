
#include "Scene.h"


bool Scene::Intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    double closestTime = MAX_DOUBLE;

    for (auto &object: objects) {
        if (object->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = tempResult.time;
            result = tempResult;
        }
    }
    return isHit;
}