#pragma once


#include <cmath>
#include <random>

//数值定义
//-------------------------------------------------------------

#define PI 3.1415926f
#define EPSILON 0.0001f

//数学
//-------------------------------------------------------------

inline float Clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float Clamp(float x){
    return Clamp(x, 0.0, 1.0);
}

//转换
//-------------------------------------------------------------

inline int Map2RGB(float x){
    return int(std::pow(Clamp(x), 1./2.2) * 255 + .5);
}


inline float Degrees2Radians(float degrees) {
    return degrees * PI / 180.0;
}

//随机数
//-------------------------------------------------------------
static std::random_device rd;
static std::mt19937 mersenne_twister(rd());
static std::uniform_real_distribution<float> uniform(0,1);

inline float RandomFloat() {
    return uniform(mersenne_twister);
}

inline float RandomFloat(float min, float max) {
    return min + (max-min) * RandomFloat();
}


