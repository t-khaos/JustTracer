#include <memory>
#include <iostream>

#include "Math/Vector.h"
#include "Object/Sphere.h"
#include "Object/Rectangle.h"
#include "Renderer/Scene.h"
#include "Renderer/Camera.h"
#include "Renderer/Sampler.h"
#include "Integrator/MonteCarloPathIntegrator.h"
#include "Renderer/Film.h"
#include "Renderer/Renderer.h"
#include "Material/DiffuseMaterial.h"
#include "Material/MirrorMaterial.h"
#include "Material/MicrofacetMaterial.h"

int main() {
    //参数
    //-------------------------------------------------------------
    const int width = 720;
    const int height = 720;
    const float aspect_ratio = static_cast<float>(width) / height;
    const float fov = 40;
    const int spp = 48;

    //材质
    //-------------------------------------------------------------
    auto redDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color(0.63f, 0.065f, 0.05f), //base color
            Color(0.0f), // emission
            MaterialType::Object
    );
    auto greenDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color(0.14f, 0.45f, 0.091f), //base color
            Color(0.0f), // emission
            MaterialType::Object
    );
    auto whiteDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color(0.725f, 0.71f, 0.68f), //base color
            Color(0.0f), // emission
            MaterialType::Object
    );
    auto lightMat = std::make_shared<DiffuseMaterial>(
            Color(0.0), //base color
            Color(50, 50, 50), // emission
            MaterialType::Light
    );
    auto mirrorMat = std::make_shared<MirrorMaterial>(
            Color(1.0f, 1.0f, 1.0f), //base color
            Color(0.0f), // emission
            MaterialType::Object
    );

    auto remapMat = std::make_shared<DiffuseMaterial>(
            Color(0.65f, 0.65f, 0.65f),
            Color(0.0f),
            MaterialType::Remap
    );

    auto mircofacetMat = std::make_shared<MicrofacetMaterial>(
            0.4f, //粗糙度
            0.9f, //金属度
            2.0f, //线性值反射率
            Color(1.0f, 1.0f, 1.0f), //基色
            Color(0.0f), //自发光
            MaterialType::Object //材质类型
    );
    auto testDiffuseMat = std::make_shared<DiffuseMaterial>(
            Color(1.0f, 1.0f, 1.0f), //base color
            Color(0.0f), // emission
            MaterialType::Object
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
    Vector3 L1(20, 99.999f, 20);// 矩形灯光顶点坐标
    Vector3 L2(-20, 99.999f, 20);
    Vector3 L3(-20, 99.999f, -20);
    Vector3 L4(20, 99.999f, -20);

    //物体
    //-------------------------------------------------------------
    auto redSphere = std::make_shared<Sphere>(30, origin, mircofacetMat);//球体

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

}
