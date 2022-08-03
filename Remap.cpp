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


    auto whiteDiffuseMat = std::make_shared<MirrorMaterial>(
            Color(1.0f, 1.0f, 1.0f), //base color
            Color(0.0f), // emission
            MaterialType::Object
    );
    auto lightMat = std::make_shared<DiffuseMaterial>(
            Color(0.0), //base color
            Color(100, 100, 100), // emission
            MaterialType::Light
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
    //坐标
    //-------------------------------------------------------------
    Vector3 origin(0, -60, 0);//球体坐标
    Vector3 A(-100, 100, 100);// 矩形 Cornell Box 顶点坐标
    Vector3 B(-1000, -100, 1000);
    Vector3 C(1000, -100, 1000);
    Vector3 D(100, 100, 100);
    Vector3 E(-100, 100, -100);
    Vector3 F(-1000, -100, -1000);
    Vector3 G(1000, -100, -1000);
    Vector3 H(100, 100, -100);
    Vector3 L1(50, 10, 10);// 矩形灯光顶点坐标
    Vector3 L2(30, 20, 10);
    Vector3 L3(50, 10, -10);
    Vector3 L4(30, 20, -10);

    //物体
    //-------------------------------------------------------------
    auto sphere = std::make_shared<Sphere>(40, origin, remapMat);//球体

    auto bottomRectangle = std::make_shared<Rectangle>(G, F, B, C, mircofacetMat);

    //光源
    //-------------------------------------------------------------
    auto lightRectangle = std::make_shared<Rectangle>(L1, L2, L3, L4, lightMat);//面光源

    //场景
    //-------------------------------------------------------------
    auto scene = std::make_shared<Scene>();

    //物体
    scene->AddObject(sphere);//添加物体
    scene->AddObject(bottomRectangle);
    scene->AddObject(lightRectangle);

    //灯光
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
