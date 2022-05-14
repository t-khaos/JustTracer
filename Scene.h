#pragma once

#include <memory>
#include <vector>

#include "Sphere.h"

struct Scene {

    std::vector<std::shared_ptr<Object>> objects;

    Scene() : objects{} {};

    void Add(std::shared_ptr<Object> object) { objects.push_back(object); }

    bool Intersect(const Ray &ray, HitResult &result) const;

    Color CastRay(const Ray &ray) const;

};

bool Scene::Intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    double time_closest = std::numeric_limits<double>::max();
    double eps = 0.0001;

    for (auto &object: objects) {
        if (object->intersect(ray, tempResult, eps, time_closest)) {
            isHit = true;
            time_closest = tempResult.time;
            result = tempResult;
        }
    }
    return isHit;
}