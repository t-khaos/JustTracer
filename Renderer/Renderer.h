#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "../Math/Global.h"
#include "Scene.h"
#include "Sampler.h"
#include "Integrator.h"
#include "Film.h"
#include "Camera.h"


struct Renderer {
    int spp;
    std::shared_ptr<Scene>  scene;
    std::shared_ptr<Camera>  camera;
    std::shared_ptr<Sampler>  sampler;
    std::shared_ptr<Film>  film;
    std::shared_ptr<Integrator>  integrator;

    Renderer(int _spp) : spp(_spp) {}

    void Render() const;
};
