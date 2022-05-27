#pragma once

#include "../Math/Vector.h"
#include "../Renderer/Renderer.h"
#include "../Material/DiffuseMaterial.h"
#include "../Object/Rectangle.h"
#include "../Object/Sphere.h"
#include "../Integrator/MonteCarloPathIntegrator.h"
#include "../Material/ReflectMaterial.h"

struct CornellBox {
    CornellBox() {}

    void Render() {
        //参数
        //-------------------------------------------------------------
        const int width = 720;
        const int height = 720;
        const float aspect_ratio = static_cast<float>(width) / height;
        const float fov = 40;
        const int spp = 240;

//材质
        //-------------------------------------------------------------
        auto redDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.63f, 0.065f, 0.05f), //base color
                Color(0.0f), // emission
                MaterialType::DIFFUSE_IDEAL
        );
        auto greenDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.14f, 0.45f, 0.091f), //base color
                Color(0.0f), // emission
                MaterialType::DIFFUSE_IDEAL
        );
        auto whiteDiffuseMat = std::make_shared<DiffuseMaterial>(
                Color(0.725f, 0.71f, 0.68f), //base color
                Color(0.0f), // emission
                MaterialType::DIFFUSE_IDEAL
        );
        auto lightMat = std::make_shared<DiffuseMaterial>(
                Color(0.0), //base color
                Color(50, 50, 50), // emission
                MaterialType::LIGHT
        );
        auto mirrorMat = std::make_shared<ReflectMaterial>(
                Color(1.0f, 1.0f, 1.0f), //base color
                Color(0.0f), // emission
                MaterialType::REFLECT
        );

        auto remapMat = std::make_shared<DiffuseMaterial>(
                Color(0.65f, 0.65f, 0.65f),
                Color(0.0f),
                MaterialType::DIFFUSE_IDEAL_REMAP
        );

        //坐标
        //-------------------------------------------------------------
        Vector3 origin(0, -70, 0);//球体坐标
        Vector3 A(-100, 100, 100);// 矩形 Cornell Box 顶点坐标
        Vector3 B(-100, -100, 100);
        Vector3 C(100, -100, 100);
        Vector3 D(100, 100, 100);
        Vector3 E(-100, 100, -100);
        Vector3 F(-100, -100, -100);
        Vector3 G(100, -100, -100);
        Vector3 H(100, 100, -100);
        Vector3 L1(20, 99.99, 20);// 矩形灯光顶点坐标
        Vector3 L2(-20, 99.99, 20);
        Vector3 L3(-20, 99.99, -20);
        Vector3 L4(20, 99.99, -20);

        //物体
        //-------------------------------------------------------------
        auto redSphere = std::make_shared<Sphere>(30, origin, redDiffuseMat);//球体

        auto bottomRectangle = std::make_shared<Rectangle>(G, F, B, C, whiteDiffuseMat);//Cornell Box
        auto topRectangle = std::make_shared<Rectangle>(H, D, A, E, whiteDiffuseMat);
        auto leftRectangle = std::make_shared<Rectangle>(A, B, F, E, redDiffuseMat);
        auto rightRectangle = std::make_shared<Rectangle>(C, D, H, G, greenDiffuseMat);
        auto backRectangle = std::make_shared<Rectangle>(E, F, G, H, whiteDiffuseMat);

        //光源
        //-------------------------------------------------------------
        auto lightRectangle = std::make_shared<Rectangle>(L1, L2, L3, L4, lightMat);//面光源

        //场景
        //-------------------------------------------------------------
        auto scene = std::make_shared<Scene>();

        scene->AddObject(redSphere);//添加物体
        scene->AddObject(bottomRectangle);
        scene->AddObject(topRectangle);
        scene->AddObject(leftRectangle);
        scene->AddObject(rightRectangle);
        scene->AddObject(backRectangle);
        scene->AddObject(lightRectangle);

        scene->AddLight(lightRectangle);//添加灯光

        //相机
        //-------------------------------------------------------------
        auto camera = std::make_shared<Camera>(
                Vector3(0, 0, 380),
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
        auto sampler = std::make_shared<Sampler>(SamplerType::Uniform);

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

/*右手坐标系
          y
          ↑
          |
      ————|————→ x
         /|
        z

 Cornell Box 平面法线都向内
       E__________H
      /|         /|
     / |   ↓    / |
   A/__|_______/D |
    | F|_______|__|G
    |  /       |  /
    | /    ↑   | /
   B|/_________|/C

 顶点顺序为逆时针 1-2-3-4
   2--------1
   |        |
   |        |
   3--------4

   */


    