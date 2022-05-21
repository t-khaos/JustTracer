#pragma once

#include <memory>
#include <vector>

#include "Shape/Sphere.h"
#include "Light/Light.h"

struct Scene {

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    Scene() : objects{} {};

    void AddObject(std::shared_ptr<Object> object) { objects.push_back(object); }
    void AddLight(std::shared_ptr<Light> light){lights.push_back(light);}

    bool Intersect(const Ray &ray, HitResult &result) const;

    Color3f CastRay(const Ray &ray) const;

};

bool Scene::Intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    float time_closest = std::numeric_limits<float>::max();
    float eps = 0.0001;

    for (auto &object: objects) {
        if (object->intersect(ray, tempResult, eps, time_closest)) {
            isHit = true;
            time_closest = tempResult.distance;
            result = tempResult;
        }
    }
    return isHit;
}

