#pragma once

#include "../Math/Vector.h"
#include "../Renderer/Renderer.h"
#include "../Material/DiffuseMaterial.h"
#include "../Object/Rectangle.h"
#include "../Object/Sphere.h"
#include "../Integrator/MonteCarloPathIntegrator.h"
#include "../Material/ReflectMaterial.h"

struct Remap {
    Remap() {}

    void Render() {
        //参数
        //-------------------------------------------------------------
        const int width = 480;
        const int height = 720;
        const double aspect_ratio = static_cast<double>(width) / height;
        const double fov = 40;
        const int spp = 48;

        //材质
        //-------------------------------------------------------------
        auto redDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color3d(0.63, 0.065, 0.05), //base color
                Color3d(0.0), // emission
                MaterialType::DIFFUSE_IDEAL
        );
        auto greenDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color3d(0.14, 0.45, 0.091),
                Color3d(0.0),
                MaterialType::DIFFUSE_IDEAL
        );
        auto whiteDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color3d(0.725, 0.71, 0.68),
                Color3d(0.0),
                MaterialType::DIFFUSE_IDEAL
        );
        auto lightMat = std::make_shared<DiffuseMaterial>(
                Color3d(0.0),
                Color3d(25, 25, 25),
                MaterialType::LIGHT
        );

        auto remapMat = std::make_shared<DiffuseMaterial>(
                Color3d(0.65, 0.65, 0.65),
                Color3d(),
                MaterialType::DIFFUSE_IDEAL_REMAP
        );

        auto mirrorMat = std::make_shared<ReflectMaterial>(
                Color3d(1.0, 1.0, 1.0), //base color
                Color3d(), // emission
                MaterialType::REFLECT
        );
        //坐标
        //-------------------------------------------------------------
        Vector3d origin(50, 0, 0);//球体坐标


        Vector3d A(1000, -50, -1000);
        Vector3d B(-1000, -50, -1000);
        Vector3d C(-1000, -50, 1000);
        Vector3d D(1000, -50, 1000);

        Vector3d L1(-40, 30, 65);// 矩形灯光顶点坐标
        Vector3d L2(-30, 50, 65);
        Vector3d L3(-30, 50, 45);
        Vector3d L4(-40, 30, 45);

        //物体
        //-------------------------------------------------------------
        auto sphere = std::make_shared<Sphere>(50, origin, remapMat);//球体

        auto bottomRectangle = std::make_shared<Rectangle>(A, B, C, D, mirrorMat);

        //光源
        //-------------------------------------------------------------
        auto lightRectangle = std::make_shared<Rectangle>(L4, L3, L2, L1, lightMat);//面光源

        //场景
        //-------------------------------------------------------------
        auto scene = std::make_shared<Scene>();

        scene->AddObject(sphere);//添加物体
        scene->AddObject(bottomRectangle);
        scene->AddObject(lightRectangle);

        scene->AddLight(lightRectangle);//添加灯光

        //相机
        //-------------------------------------------------------------
        auto camera = std::make_shared<Camera>(
                Vector3d(0, 0, 600),
                Vector3d(0, 0, 0),
                Vector3d(0, 1, 0),
                fov,
                aspect_ratio
        );

        //积分器
        //-------------------------------------------------------------
        auto integrator = std::make_shared<MonteCarloPathIntegrator>(8);

        //采样器
        //-------------------------------------------------------------
        auto sampler = std::make_shared<Sampler>(SamplerType::Trapezoidal);

        //胶片
        //-------------------------------------------------------------
        auto film = std::make_shared<Film>(width, height);
        film->fileName = "test.ppm";

        Renderer renderer(spp);

        renderer.camera = camera;
        renderer.film = film;
        renderer.scene = scene;
        renderer.sampler = sampler;
        renderer.integrator = integrator;

        renderer.Render();
    };
};