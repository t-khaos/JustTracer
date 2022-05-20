#include <iostream>
#include "Renderer.h"
#include "Material/MicrofacetMaterial.h"
#include "Sampler/TrapezoidalSampler.h"
#include "Integrator/NormalIntegrator.h"
#include "Tool/Vector3.h"
#include "Integrator/SimplePathIntegrator.h"
#include "Material/DiffuseMaterial.h"
#include "Material/RefractMaterial.h"
#include "Integrator/MonteCarloPathIntegrator.h"

int main() {

    //参数
    //-------------------------------------------------------------
    const int width = 720;
    const int height = 480;
    const float aspect_ratio = static_cast<float>(width) / height;
    const float fov = 90;
    const int spp = 100;

    //材质
    //-------------------------------------------------------------

    auto mat_diffuse_red = std::make_shared<DiffuseMaterial>(Color(0.63f, 0.065f, 0.05f), Color(0), MaterialType::DIFFUSE);
    auto mat_diffuse_green = std::make_shared<DiffuseMaterial>(Color(0.14f, 0.45f, 0.091f), Color(0), MaterialType::DIFFUSE);
    auto mat_diffuse_white = std::make_shared<DiffuseMaterial>(Color(0.725f, 0.71f, 0.68f), Color(0), MaterialType::DIFFUSE);

    auto mat_light = std::make_shared<DiffuseMaterial>(Color(0.65,0.65,0.65), Color(50,50,50), MaterialType::LIGHT);
    //物体
    //-------------------------------------------------------------
    auto sphere_left = std::make_shared<Sphere>(1e5, Vec3(-1e5-150,0,0),mat_diffuse_red);
    auto sphere_right = std::make_shared<Sphere>(1e5, Vec3(1e5+150,0,0), mat_diffuse_green);
    auto sphere_back = std::make_shared<Sphere>(1e5, Vec3(0,0, 1e5+150), mat_diffuse_white);
    auto sphere_bottom = std::make_shared<Sphere>(1000, Vec3(0, -1050, 0), mat_diffuse_white);
    auto sphere_top = std::make_shared<Sphere>(1e5, Vec3(0,1e5+150,0), mat_diffuse_white);


    auto sphere_light = std::make_shared<Sphere>(20, Vec3(0,60,0),mat_light);

    //光源
    //-------------------------------------------------------------
    auto light = std::make_shared<Light>(sphere_light);

    //场景
    //-------------------------------------------------------------
    auto scene = std::make_shared<Scene>();
    //scene->AddObject(sphere_top);
    scene->AddObject(sphere_bottom);
    //scene->AddObject(sphere_back);
    //scene->AddObject(sphere_left);
    //scene->AddObject(sphere_right);

    scene->AddObject(sphere_light);

    scene->AddLight(light);

    //相机
    //-------------------------------------------------------------
    auto camera = std::make_shared<PerspectiveCamera>(
            Vec3(0, 0, -150),
            Vec3(0, 0, 0),
            Vec3(0, 1, 0),
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
    film->filename = "test.ppm";

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
