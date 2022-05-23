#pragma once

#include <memory>
#include <vector>
#include "Object/IIntersect.h"
#include "Object/ILight.h"

struct Scene : IIntersect{

    std::vector<std::shared_ptr<IIntersect>> objects;
    std::vector<std::shared_ptr<ILight>> lights;

    Scene() : objects{} {};

    void AddObject(std::shared_ptr<IIntersect> object) { objects.push_back(object); }
    void AddLight(std::shared_ptr<ILight> light){lights.push_back(light);}

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;
};

inline bool Scene::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    HitResult tempResult;
    bool isHit = false;
    float closestTime = t_near;

    for (auto &object: objects) {
        if (object->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = tempResult.distance;
            result = tempResult;
        }
    }
    return isHit;
}

