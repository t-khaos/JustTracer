
#include "Renderer.h"
#include "../Math/Math.h"

void Film::Develop(const std::vector<Color3d> &pixels) const {
    std::ofstream file;
    file.open(fileName);
    file << "P3\n" << width << "\n" << height << "\n255\n";
    for (int i = 0; i < width * height; i++)
        file << Map2RGB(pixels[i].x) << " " << Map2RGB(pixels[i].y) << " " << Map2RGB(pixels[i].z) << " ";
    file.close();
}