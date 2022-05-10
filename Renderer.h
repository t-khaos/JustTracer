#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Scene.h"
#include "Math.h"
#include "Camera/PerspectiveCamera.h"
#include "Sampler/TrapezoidalSampler.h"

struct Renderer {

    void draw(const Scene &scene, const PerspectiveCamera &camera, int spp);
};

void Renderer::draw(const Scene &scene, const PerspectiveCamera &camera, int spp) {
    std::vector<Color> pixels(scene.width * scene.height);
    Color color;
    //2x2 subpixel sampler
    TrapezoidalSampler sampler(2,2);
#pragma omp parallel for schedule(dynamic, 1) private(color)
    for (int y = scene.height - 1; y >= 0; --y) {
        std::cout << "Rendering " << spp << " spp: " << 100.0 * (scene.height - 1 - y) / (scene.height - 1) << "%"
                  << std::endl;
        for (int x = 0; x < scene.width; x++) {
            color = Color();
            for (int index = 0; index < spp; index++) {
                Ray ray = camera.GetRay(sampler.Sample(x,y));
                color += scene.cast_ray(ray);
            }
            pixels[(scene.height - y - 1) * scene.width + x] = color * 0.25 * (1 / static_cast<double>(spp));
        }
    }

    std::string filename =
            "result_" + std::to_string(scene.height) + "p_" + std::to_string(spp * 4) + "spp" + ".ppm";
    std::ofstream file;
    file.open(filename);
    file << "P3\n" << scene.width << "\n" << scene.height << "\n255\n";
    for (int i = 0; i < scene.width * scene.height; i++)
        file << toInt(pixels[i].x) << " " << toInt(pixels[i].y) << " " << toInt(pixels[i].z) << " ";
    file.close();

    std::cout << "\nDone." << std::endl;
}