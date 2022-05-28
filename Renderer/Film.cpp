
#include "Renderer.h"
#include "../Math/Math.h"

void Film::Develop(const std::vector<Color> &pixels) const {
    std::ofstream file;
    file.open(fileName);
    file << "P3\n" << width << "\n" << height << "\n255\n";
    for (int i = 0; i < width * height; i++)
        file << ToRGB(pixels[i].x) << " " << ToRGB(pixels[i].y) << " " << ToRGB(pixels[i].z) << " ";
    file.close();
}