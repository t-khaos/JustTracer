#include <iostream>
#include "Renderer.h"

int main() {

    const int width = 720;
    const int height= 480;
    const double aspect_ratio = static_cast<double>(width)/height;
    const double fov=90;

    Renderer renderer;

    PerspectiveCamera camera(
            Vec3(0.0,0.0,0.0),
            Vec3(0.0,0.0,-1.0),
            Vec3(0,1,0),
            fov,
            aspect_ratio
    );

    Scene scene(width,height);

    auto sphere_center = std::make_shared<Sphere>(0.5,Vec3(0,0,-1));

    scene.add(sphere_center);

    renderer.draw(scene,camera,25);
}
