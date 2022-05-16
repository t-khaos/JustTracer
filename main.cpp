#include <iostream>
#include "Renderer.h"
#include "Material/MicrofacetMaterial.h"
#include "Sampler/TrapezoidalSampler.h"
#include "Integrator/NormalIntegrator.h"
#include "Tool/Vector3.h"
#include "Integrator/PathIntegrator.h"
#include "Material/DiffuseMaterial.h"

int main() {

    //参数
    //-------------------------------------------------------------
    const int width = 720;
    const int height = 480;
    const double aspect_ratio = static_cast<double>(width) / height;
    const double fov = 90;
    const int spp = 100;

    //材质
    //-------------------------------------------------------------

    DiffuseMaterial mat_diffuse_ground(Color(0.8, 0.8, 0.0),MaterialType::DIFFUSE);
    DiffuseMaterial mat_diffuse_center(Color(0.7, 0.3, 0.3),MaterialType::DIFFUSE);
    RefractMaterial mat_refract_left(Color(0.8, 0.8, 0.8), MaterialType::REFRACT);
    RefractMaterial mat_refract_right(Color(0.8, 0.6, 0.2), MaterialType::REFRACT);
    //物体
    //-------------------------------------------------------------

    auto sphere_ground = std::make_shared<Sphere>(100.0, Vec3(0.0, -100.5, -1.0),&mat_diffuse_ground);
    auto sphere_center = std::make_shared<Sphere>(0.5, Vec3(0, 0, -1),&mat_diffuse_center);
    auto sphere_right = std::make_shared<Sphere>(0.5, Vec3(1, 0, -1),&mat_refract_right);
    auto sphere_left = std::make_shared<Sphere>(0.5, Vec3(-1, 0, -1),&mat_refract_left);

    //场景
    //-------------------------------------------------------------
    Scene scene;

    scene.Add(sphere_ground);
    scene.Add(sphere_center);
    scene.Add(sphere_left);
    scene.Add(sphere_right);

    //相机
    //-------------------------------------------------------------
    PerspectiveCamera camera(
            Vec3(0.0, 0.0, 0.0),
            Vec3(0.0, 0.0, -1.0),
            Vec3(0, 1, 0),
            fov,
            aspect_ratio
    );

    //积分器
    //-------------------------------------------------------------
    PathIntegrator integrator(5);

    //采样器
    //-------------------------------------------------------------
    TrapezoidalSampler sampler;

    //胶片
    //-------------------------------------------------------------
    Film film(width, height);
    film.filename = "test.ppm";

    //渲染
    //-------------------------------------------------------------
    Renderer renderer(spp);

    renderer.SetCamera(&camera);
    renderer.SetFilm(&film);
    renderer.SetScene(&scene);
    renderer.SetSampler(&sampler);
    renderer.SetIntegrator(&integrator);

    renderer.Render();

}
