#pragma once

#include <random>

struct Random {
    std::random_device rd;
    std::mt19937 mersenneTwister;
    std::uniform_real_distribution<double> uniform;

    Random();

    double RandomDouble();

    double RandomDouble(double min, double max);
};

Random::Random() {
    mersenneTwister = std::mt19937(rd());
    uniform = std::uniform_real_distribution<double>(0, 1);
}

double Random::RandomDouble() {
    return uniform(mersenneTwister);
}

double Random::RandomDouble(double min, double max) {
    return min + (max - min) * RandomDouble();
}