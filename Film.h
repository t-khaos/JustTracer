#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Math/Vector3.h"
#include "Math.h"

struct Film{
    std::vector<Color> pixels;
    std::string filename;
    int width;
    int height;

    Film(int _w, int _h):width(_w),height(_h){}

    void SetFileName(std::string& name, int spp);
    void StoreImage();
};
void Film::SetFileName(std::string& name, int spp){
    filename = name + std::to_string(spp) + "spp.ppm";
}

void Film::StoreImage() {
    std::ofstream file;
    file.open(filename);
    file << "P3\n" << width << "\n" << height << "\n255\n";
    for (int i = 0; i < width * height; i++)
        file << toInt(pixels[i].x) << " " << toInt(pixels[i].y) << " " << toInt(pixels[i].z) << " ";
    file.close();
}