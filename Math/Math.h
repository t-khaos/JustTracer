#pragma once


#include <cmath>
#include <algorithm>
#include "Global.h"

inline int Mix(float x, float y, float t) {
    return (1.0f - t) * x + t * y;
}

inline int ToRGB(float x) {
    return int(std::pow(std::clamp(x, 0.0f, 1.0f), 1.0f / 2.2f) * 255 + 0.5f);
}


inline float ToRadians(float degrees) {
    return degrees * PI / 180.0;
}

inline float RemapRange(float num, Range range) {
    assert(range.left != range.right);
    if (num >= range.right)
        return 1.0f;
    if (num <= range.left)
        return 0.0f;
    return (num - range.left) / (range.right - range.left);
}

inline float ToGrayScale(const Color &color) {
    return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;;
}

inline Color RemapColor(const Color &color) {
    //RGB重映射为灰度值
    float grayScale = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;

    grayScale = RemapRange(grayScale, Range(0.15, 0.4));

    Color RGB;

    //灰度值重映射为热图
    if (grayScale <= 1.0f && grayScale > 0.75f) {
        RGB.r = 1.0f;
        RGB.g = 1.0f - RemapRange(grayScale, Range(0.75, 1));
        RGB.b = 0.0f;
    } else if (grayScale <= 0.75 && grayScale > 0.5f) {
        RGB.r = RemapRange(grayScale, Range(0.5f, 0.75f));
        RGB.g = 1.0f;
        RGB.b = 0.0f;
    } else if (grayScale <= 0.55f && grayScale > 0.25f) {
        RGB.r = 0;
        RGB.g = 1.0f;
        RGB.b = 1.0f - RemapRange(grayScale, Range(0.25f, 0.5f));
    } else if (grayScale <= 0.25f && grayScale >= 0.0f) {
        RGB.r = 0.0f;
        RGB.g = RemapRange(grayScale, Range(0.0f, 0.25f));
        RGB.b = 1.0f;
    }
    return RGB;
}