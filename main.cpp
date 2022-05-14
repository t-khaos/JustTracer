#include <iostream>
#include "Renderer.h"
#include "Material/MicrofacetMaterial.h"
#include "Sampler/TrapezoidalSampler.h"
#include "Integrator/NormalIntegrator.h"
#include "Tool/Vector3.h"

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


    //物体
    //-------------------------------------------------------------
    std::shared_ptr<Sphere> sphere_center = std::make_shared<Sphere>(0.5, Vec3(0, 0, -1));


    //场景
    //-------------------------------------------------------------
    Scene scene;

    scene.Add(sphere_center);



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
    NormalIntegrator integrator;

    //采样器
    //-------------------------------------------------------------
    TrapezoidalSampler sampler;

    //胶片
    //-------------------------------------------------------------
    Film film(width, height);

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
