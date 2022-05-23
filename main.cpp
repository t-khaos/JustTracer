#include <iostream>
#include "Renderer.h"
#include "Material/MicrofacetMaterial.h"
#include "Sampler/TrapezoidalSampler.h"
#include "Integrator/NormalIntegrator.h"
#include "Tool/Vector.h"
#include "Integrator/SimplePathIntegrator.h"
#include "Material/DiffuseMaterial.h"
#include "Material/RefractMaterial.h"
#include "Integrator/MonteCarloPathIntegrator.h"
#include "Shape/Model.h"
#include "Light/AreaLight.h"

int main() {

    Vector3f x(1,0,0);
    Vector3f y(0,1,0);
    auto z = Cross(x,y);


    //参数
    //-------------------------------------------------------------
    const int width = 720;
    const int height = 480;
    const float aspect_ratio = static_cast<float>(width) / height;
    const float fov = 45;
    const int spp = 100;

    //材质
    //-------------------------------------------------------------

    auto mat_diffuse_red = std::make_shared<DiffuseMaterial>(
            Color3f(0.63f, 0.065f, 0.05f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );
    auto mat_diffuse_green = std::make_shared<DiffuseMaterial>(
            Color3f(0.14f, 0.45f, 0.091f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );
    auto mat_diffuse_white = std::make_shared<DiffuseMaterial>(
            Color3f(0.725f, 0.71f, 0.68f), //base color
            Color3f(0.f), // emission
            MaterialType::DIFFUSE
    );

    auto mat_light = std::make_shared<DiffuseMaterial>(
            Color3f(0.f), //base color
            Color3f(50, 50, 50), // emission
            MaterialType::LIGHT
    );

    //物体
    //-------------------------------------------------------------

    //几何物体 - 球体
    auto sphere_bottom = std::make_shared<Sphere>(2000, Vector3f(0, -2060, 0), mat_diffuse_white);
    auto sphere_red = std::make_shared<Sphere>(35, Vector3f(0, 0, 0), mat_diffuse_red);
    auto sphere_test = std::make_shared<Sphere>(35, Vector3f(120, 0, 0), mat_diffuse_red);

    auto sphere_light = std::make_shared<Sphere>(30, Vector3f(0, 180, 0), mat_light);

    // 坐标系为右手坐标系
    //          y
    //          ↑
    //          |
    //      ————|————→ x
    //         /|
    //        z

    // 为实现 Cornell Box ，平面法线都向内
    //       E__________H
    //      /|         /|
    //     / |   ↓    / |
    //   A/__|_______/D |
    //    | F|_______|__|G
    //    |  /       |  /
    //    | /    ↑   | /
    //   B|/_________|/C

    // 注意三角形拼接顺序为逆时针
    // 1-2-3 | 3-4-1
    //   2*  *  *  *  *1
    //    *        *  *
    //    *     *     *
    //    *  *        *
    //   3*  *  *  *  *4

    // Cornell Box 顶点坐标

    Vector3f A(-100, 100, 100);
    Vector3f B(-100, -100, 100);
    Vector3f C(100, -100, 100);
    Vector3f D(100, 100, 100);

    Vector3f E(-100, 100, -100);
    Vector3f F(-100, -100, -100);
    Vector3f G(100, -100, -100);
    Vector3f H(100, 100, -100);

    // 灯光顶点坐标
    Vector3f L1(30, 99, 30);
    Vector3f L2(-30, 99, 30);
    Vector3f L3(-30, 99, -30);
    Vector3f L4(30, 99, -30);
    //灯光三角形
    //灯光三角形
    auto lightTriangleA = std::make_shared<Triangle>(L1,L2,L3);
    auto lightTriangleB = std::make_shared<Triangle>(L3,L4,L1);

    //地板三角形
    auto bottomTriangleA = std::make_shared<Triangle>(G, F, B);
    auto bottomTriangleB = std::make_shared<Triangle>(B, C, G);

    //天花板三角形
    auto topTriangleA = std::make_shared<Triangle>(D, A, E);
    auto topTriangleB = std::make_shared<Triangle>(E, H, D);

    //左侧三角形
    auto leftTriangleA = std::make_shared<Triangle>(E, A, B);
    auto leftTriangleB = std::make_shared<Triangle>(B, F, E);

    //右侧三角形
    auto rightTriangleA = std::make_shared<Triangle>(D, H, G);
    auto rightTriangleB = std::make_shared<Triangle>(G, C, D);

    //后侧三角形
    auto backTriangleA = std::make_shared<Triangle>(H, E, F);
    auto backTriangleB = std::make_shared<Triangle>(F, G, H);


    //灯光三角形网格
    auto lightMesh = std::make_shared<Mesh>(mat_light);
    lightMesh->AddTriangle(lightTriangleA);
    lightMesh->AddTriangle(lightTriangleB);

    //地板三角形网格
    auto bottomMesh = std::make_shared<Mesh>(mat_diffuse_white);
    bottomMesh->AddTriangle(bottomTriangleA);
    bottomMesh->AddTriangle(bottomTriangleB);

    //地板三角形网格
    auto topMesh = std::make_shared<Mesh>(mat_diffuse_white);
    topMesh->AddTriangle(topTriangleA);
    topMesh->AddTriangle(topTriangleB);

    //左侧三角形网格
    auto leftMesh = std::make_shared<Mesh>(mat_diffuse_red);
    leftMesh->AddTriangle(leftTriangleA);
    leftMesh->AddTriangle(leftTriangleB);

    //右侧三角形网格
    auto rightMesh = std::make_shared<Mesh>(mat_diffuse_green);
    rightMesh->AddTriangle(rightTriangleA);
    rightMesh->AddTriangle(rightTriangleB);

    //后侧三角形网格
    auto backMesh = std::make_shared<Mesh>(mat_diffuse_white);
    backMesh->AddTriangle(backTriangleA);
    backMesh->AddTriangle(backTriangleB);


    //光源
    //-------------------------------------------------------------
    auto light_sphere = std::make_shared<SphereLight>(sphere_light);
    auto light_area = std::make_shared<AreaLight>(lightMesh);

    //场景
    //-------------------------------------------------------------
    auto scene = std::make_shared<Scene>();
    //添加物体
    //scene->AddObject(sphere_bottom);
    scene->AddObject(sphere_red);
    //scene->AddObject(sphere_test);

    //添加Mesh
    scene->AddObject(topMesh);
    scene->AddObject(bottomMesh);
    //scene->AddObject(leftMesh);
    //scene->AddObject(rightMesh);
    //scene->AddObject(backMesh);

    //添加灯光
    scene->AddObject(lightMesh);
    scene->AddLight(light_area);
    //scene->AddObject(sphere_light);
    //scene->AddLight(light_sphere);

    //相机
    //-------------------------------------------------------------
    auto camera = std::make_shared<PerspectiveCamera>(
            Vector3f(0, 0, 300),
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

    renderer.SetCamera(camera);
    renderer.SetFilm(film);
    renderer.SetScene(scene);
    renderer.SetSampler(sampler);
    renderer.SetIntegrator(integrator);

    renderer.Render();

}
