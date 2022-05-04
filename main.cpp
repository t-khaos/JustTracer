#include <iostream>
#include "Renderer.h"

int main() {

    const int width = 400;
    const double aspect_ratio = 16.0/9.0;
    const int height= static_cast<int>(400/aspect_ratio);
    const double fov=90;

    Renderer renderer;

    Camera camera(
            Vec3(0.0,0.0,0.0),
            Vec3(0.0,0.0,-1.0),
            Vec3(0,1,0),
            fov,
            aspect_ratio
    );

    Scene scene(width,height);

    auto sphere_center = std::make_shared<Sphere>(0.5,Vec3(0,0,-1));

    scene.Add(sphere_center);

    renderer.Render(scene,camera,10);
}
