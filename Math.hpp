#pragma once


#include <cmath>
#include <random>


#define PI 3.1415926535897932385

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double clamp(double x){
    return clamp(x,0.0,1.0);
}

inline int toInt(double x){
    return int(std::pow(clamp(x),1)*255+.5);
}


inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

//random
static std::random_device rd;
static std::mt19937 mersenneTwister(rd());
static std::uniform_real_distribution<double> uniform(0,1);

inline double random_double() {
    return uniform(mersenneTwister);
}

/*inline double random_double() {
    return (double)rand() / (double)RAND_MAX;
}*/

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}


