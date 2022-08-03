#pragma once

#include <memory>
#include <vector>

#include "../Math/Global.h"
#include "../Common/Object.h"
#include "../Common/Light.h"
#include "../Common/LightResult.h"

struct Scene {

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;

    Scene() : objects{} {};

    void AddObject(std::shared_ptr<Object> object) { objects.push_back(object); }

    void AddLight(std::shared_ptr<Light> light) { lights.push_back(light); }

    bool Intersect(Ray &ray, HitResult &result) const;

    void SampleLight(LightResult &result) const;
};



