#pragma once

#include <random>

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