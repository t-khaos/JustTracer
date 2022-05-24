#pragma once

#include <string>

#include "../Common/Global.h"

struct Film {
    std::string fileName;
    int width;
    int height;

    Film(const int &_w, const int &_h)
            : width(_w), height(_h), fileName("output.ppm") {}

    void Develop(const std::vector<Color3d> &pixels) const;
};