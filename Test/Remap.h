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
        const float aspect_ratio = static_cast<float>(width) / height;
        const float fov = 40;
        const int spp = 48;

        //材质
        //-------------------------------------------------------------
        auto redDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.63, 0.065, 0.05), //base color
                Color(0.0), // emission
                MaterialType::DIFFUSE_IDEAL
        );
        auto greenDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.14, 0.45, 0.091),
                Color(0.0),
                MaterialType::DIFFUSE_IDEAL
        );
        auto whiteDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.725, 0.71, 0.68),
                Color(0.0),
                MaterialType::DIFFUSE_IDEAL
        );
        auto lightMat = std::make_shared<DiffuseMaterial>(
                Color(0.0),
                Color(25, 25, 25),
                MaterialType::LIGHT
        );

        auto remapMat = std::make_shared<DiffuseMaterial>(
                Color(0.65, 0.65, 0.65),
                Color(),
                MaterialType::DIFFUSE_IDEAL_REMAP
        );

        auto mirrorMat = std::make_shared<ReflectMaterial>(
                Color(1.0, 1.0, 1.0), //base color
                Color(), // emission
                MaterialType::REFLECT
        );
        //坐标
        //-------------------------------------------------------------
        Vector3 origin(50, 0, 0);//球体坐标


        Vector3 A(1000, -50, -1000);
        Vector3 B(-1000, -50, -1000);
        Vector3 C(-1000, -50, 1000);
        Vector3 D(1000, -50, 1000);

        Vector3 L1(-40, 30, 65);// 矩形灯光顶点坐标
        Vector3 L2(-30, 50, 65);
        Vector3 L3(-30, 50, 45);
        Vector3 L4(-40, 30, 45);

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
                Vector3(0, 0, 600),
                Vector3(0, 0, 0),
                Vector3(0, 1, 0),
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