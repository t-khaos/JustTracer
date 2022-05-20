#pragma once


#include "../Tool/Vector3.h"
#include "../Ray.h"
#include "../Scene.h"


struct Integrator{
    virtual Color Li(const Ray& ray, std::shared_ptr<Scene> scene) =0;
};

