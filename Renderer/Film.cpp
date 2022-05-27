
#include "Renderer.h"
#include "../Math/Math.h"

void Film::Develop(const std::vector<Color3d> &pixels) const {
    std::ofstream file;
    file.open(fileName);
    file << "P3\n" << width << "\n" << height << "\n255\n";
    for (int i = 0; i < width * height; i++)
        file << DoubleToRGB8(pixels[i].x) << " " << DoubleToRGB8(pixels[i].y) << " " << DoubleToRGB8(pixels[i].z) << " ";
    file.close();
}