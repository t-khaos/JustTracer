#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Tool/Vector3.h"
#include "Tool/Global.h"

struct Film {
    std::string filename;
    int width;
    int height;

    Film(const int &_w, const int &_h)
            : width(_w), height(_h), filename("output.ppm") {}

    void Develop(const std::vector<Color> &pixels) const;
};


void Film::Develop(const std::vector<Color> &pixels) const {
    std::ofstream file;
    file.open(filename);
    file << "P3\n" << width << "\n" << height << "\n255\n";
    for (int i = 0; i < width * height; i++)
        file << Map2RGB(pixels[i].x) << " " << Map2RGB(pixels[i].y) << " " << Map2RGB(pixels[i].z) << " ";
    file.close();
}