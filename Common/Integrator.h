#pragma once

#include "Global.h"
#include "Vector.h"
#include "Ray.h"
#include "../Renderer/World.h"

struct Integrator {
    virtual Color3d Li(const Ray &ray, std::shared_ptr<World> scene) = 0;
};


