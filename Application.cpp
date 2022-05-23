#include <iostream>

#include "Common/Vector.h"
#include "Renderer/Renderer.h"
#include "Material/DiffuseMaterial.h"
#include "Object/Rectangle.h"
#include "Object/Sphere.h"
#include "Camera/PerspectiveCamera.h"
#include "Integrator/MonteCarloPathIntegrator.h"
#include "Sampler/TrapezoidalSampler.h"

int main() {
    // 右手坐标系
    //          y
    //          ↑
    //          |
    //      ————|————→ x
    //         /|
    //        z

    // Cornell Box 平面法线都向内
    //       E__________H
    //      /|         /|
    //     / |   ↓    / |
    //   A/__|_______/D |
    //    | F|_______|__|G
    //    |  /       |  /
    //    | /    ↑   | /
    //   B|/_________|/C

    // 顶点顺序为逆时针 1-2-3-4
    //   2--------1
    //   |        |
    //   |        |
    //   3--------4

    //参数
    //-------------------------------------------------------------
    const int width = 720;
    const int height = 720;
    const float aspect_ratio = static_cast<float>(width) / height;
    const float fov = 40;
    const int spp = 100;

    //材质
    //-------------------------------------------------------------
    auto redDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color3f(0.63f, 0.065f, 0.05f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );
    auto greenDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color3f(0.14f, 0.45f, 0.091f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );
    auto whiteDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color3f(0.725f, 0.71f, 0.68f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );
    auto lightMat = std::make_shared<DiffuseMaterial>(
            Color3f(0.f), //base color
            Color3f(50, 50, 50), // emission
            MaterialType::LIGHT
    );

    //坐标
    //-------------------------------------------------------------
    Vector3f origin(0,-70,0);//球体坐标
    Vector3f A(-100, 100, 100);// 矩形 Cornell Box 顶点坐标
    Vector3f B(-100, -100, 100);
    Vector3f C(100, -100, 100);
    Vector3f D(100, 100, 100);
    Vector3f E(-100, 100, -100);
    Vector3f F(-100, -100, -100);
    Vector3f G(100, -100, -100);
    Vector3f H(100, 100, -100);
    Vector3f L1(20, 99.99, 20);// 矩形灯光顶点坐标
    Vector3f L2(-20, 99.99, 20);
    Vector3f L3(-20, 99.99, -20);
    Vector3f L4(20, 99.99, -20);

    //物体
    //-------------------------------------------------------------
    auto redSphere = std::make_shared<Sphere>(30, origin, redDiffuseMat);//球体

    auto bottomRectangle = std::make_shared<Rectangle>(G, F, B, C, whiteDiffuseMat);//Cornell Box
    auto topRectangle = std::make_shared<Rectangle>(H,D,A,E, whiteDiffuseMat);
    auto leftRectangle = std::make_shared<Rectangle>(A, B, F, E, redDiffuseMat);
    auto rightRectangle = std::make_shared<Rectangle>(C, D, H, G, greenDiffuseMat);
    auto backRectangle = std::make_shared<Rectangle>(E,F,G,H, whiteDiffuseMat);

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
    auto camera = std::make_shared<PerspectiveCamera>(
            Vector3f(0, 0, 380),
            Vector3f(0, 0, 0),
            Vector3f(0, 1, 0),
            fov,
            aspect_ratio
    );

    //积分器
    //-------------------------------------------------------------
    auto integrator = std::make_shared<MonteCarloPathIntegrator>(8);

    //采样器
    //-------------------------------------------------------------
    auto sampler = std::make_shared<TrapezoidalSampler>();

    //胶片
    //-------------------------------------------------------------
    auto film = std::make_shared<Film>(width, height);
    film->fileName = "test.ppm";

    //渲染器
    //-------------------------------------------------------------
    Renderer renderer(spp);

    renderer.camera = camera;
    renderer.film = film;
    renderer.scene=scene;
    renderer.sampler=sampler;
    renderer.integrator=integrator;

    renderer.Render();

}
