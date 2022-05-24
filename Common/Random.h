#pragma once

#include <random>

//随机数
//-------------------------------------------------------------
static std::random_device rd;
static std::mt19937 mersenne_twister(rd());
static std::uniform_real_distribution<double> uniform(0,1);

inline double RandomDouble() {
    return uniform(mersenne_twister);
}

inline double RandomDouble(double min, double max) {
    return min + (max-min) * RandomDouble();
}