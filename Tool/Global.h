#pragma once


#include <cmath>
#include <random>

//数值定义
//-------------------------------------------------------------

#define PI 3.1415926535897932385
#define EPS 0.0001

//数学
//-------------------------------------------------------------

inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double Clamp(double x){
    return Clamp(x, 0.0, 1.0);
}

//转换
//-------------------------------------------------------------

inline int Map2RGB(double x){
    return int(std::pow(Clamp(x), 1./2.2) * 255 + .5);
}


inline double Degrees2Radians(double degrees) {
    return degrees * PI / 180.0;
}

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


