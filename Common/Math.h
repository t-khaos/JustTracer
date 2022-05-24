#pragma once


#include <cmath>
#include "Global.h"


inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


inline double Clamp(double x){
    return Clamp(x, 0.0, 1.0);
}

inline int Map2RGB(double x){
    return int(std::pow(Clamp(x), 1.0/2.2) * 255 + 0.5);
}


inline double Degrees2Radians(double degrees) {
    return degrees * PI / 180.0;
}