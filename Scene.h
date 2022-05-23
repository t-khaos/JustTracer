#pragma once

#include <memory>
#include <vector>

#include "Shape/Sphere.h"
#include "Light/SphereLight.h"

struct Scene {

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    Scene() : objects{} {};

    void AddObject(std::shared_ptr<Object> object) { objects.push_back(object); }
    void AddLight(std::shared_ptr<Light> light){lights.push_back(light);}

    bool Intersect(const Ray &ray, HitResult &result) const;
};

inline bool Scene::Intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    float time_closest = std::numeric_limits<float>::max();

    for (auto &object: objects) {
        if (object->intersect(ray, tempResult, time_closest)) {
            isHit = true;
            time_closest = tempResult.distance;
            result = tempResult;
        }
    }
    return isHit;
}

