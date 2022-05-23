#pragma once

#include "Global.h"
#include "Vector.h"
#include "Ray.h"
#include "../Renderer/Scene.h"

struct Integrator {
    virtual Color3f Li(const Ray &ray, std::shared_ptr<Scene> scene) = 0;
};


