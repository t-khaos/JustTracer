#pragma once

#include <memory>
#include <vector>

#include "Shape/Sphere.h"
#include "Light/SphereLight.h"

struct Scene : Object{

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    Scene() : objects{} {};

    void AddObject(std::shared_ptr<Object> object) { objects.push_back(object); }
    void AddLight(std::shared_ptr<Light> light){lights.push_back(light);}

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

