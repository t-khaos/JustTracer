#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Scene.hpp"
#include "Math.hpp"
#include "Camera.hpp"

struct Renderer {

    void draw(const Scene &scene, const Camera &camera, int spp);
};

void Renderer::draw(const Scene &scene, const Camera &camera, int spp) {
    std::vector<Color> pixels(scene.width * scene.height);
    Color color;
#pragma omp parallel for schedule(dynamic, 1) private(color)
    for (int y = scene.height - 1; y >= 0; --y) {
        std::cout << "Rendering " << spp << " spp: " << 100.0 * (scene.height - 1 - y) / (scene.height - 1) << "%"
                  << std::endl;
        for (int x = 0; x < scene.width; x++) {
            color = Color();
            for (int sy = 0; sy < 2; sy++) {
                for (int sx = 0; sx < 2; sx++) {
                    for (int index = 0; index < spp; index++) {
                        double r1 = 2 * random_double();
                        double r2 = 2 * random_double();

                        double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
                        double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

                        double s = (static_cast<double>(x) + (dx + sx + 0.5) / 2) / (scene.width - 1);
                        double t = (static_cast<double>(y) + (dy + sy + 0.5) / 2) / (scene.height - 1);

                        Ray ray = camera.get_ray(s, t);
                        color += scene.cast_ray(ray);
                    }
                }
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