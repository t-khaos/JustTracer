#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Scene.h"
#include "Tool/Global.h"
#include "Camera/PerspectiveCamera.h"
#include "Film.h"
#include "Sampler/ISampler.h"
#include "Integrator/IIntegrator.h"

class Renderer {
private:
    std::shared_ptr<Scene>  scene = nullptr;
    std::shared_ptr<ICamera>  camera = nullptr;
    std::shared_ptr<ISampler>  sampler = nullptr;
    std::shared_ptr<Film>  film = nullptr;
    std::shared_ptr<IIntegrator>  integrator = nullptr;

    int spp;

public:
    explicit Renderer(int _spp) : spp(_spp) {}

    void SetScene(std::shared_ptr<Scene> _scene) { scene = _scene; }

    void SetCamera(std::shared_ptr<ICamera> _camera) { camera = _camera; }

    void SetSampler(std::shared_ptr<ISampler> _sample) { sampler = _sample; }

    void SetFilm(std::shared_ptr<Film> _film) { film = _film; }

    void SetIntegrator(std::shared_ptr<IIntegrator> _integrator) { integrator = _integrator; }

    void Render() const;
};


inline void Renderer::Render() const {

    std::vector<Color3f> pixels(film->width * film->height);
    Color3f color(0.0);

    //多线程计算每个像素的颜色
#pragma omp parallel for schedule(dynamic, 1) private(color)
    for (int y = film->height - 1; y >= 0; --y) {
        std::cout << 100.0 * (film->height - 1 - y) / (film->height - 1) << "%" << std::endl;
        for (int x = 0; x < film->width; x++) {
            color = Color3f(0.0);
            for (int index = 0; index < spp; index++) {
                //根据采样分布计算投射的光线方向参数
                auto position = sampler->CastRayByDistribution(x, y);
                float s = position.x / (film->width - 1);
                float t = position.y / (film->height - 1);
                //投射光线并累计颜色
                Ray ray = camera->GetRay(s, t);
                color += integrator->Li(ray, scene);
            }
            //将颜色处理后写入像素
            pixels[(film->height - y - 1) * film->width + x] = color * (1 / static_cast<float>(spp));
        }
    }

    //冲洗胶卷
    film->Develop(pixels);
}