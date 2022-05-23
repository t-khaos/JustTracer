#pragma once


#include "../Tool/Vector.h"
#include "../Ray.h"
#include "../Scene.h"


struct IIntegrator {
    virtual Color3f Li(const Ray &ray, std::shared_ptr<Scene> scene) = 0;
};

