#pragma once

#include "Sampler.h"

struct TrapezoidalSampler : public Sampler {
    int row;
    int col;
    int index = 0;

    TrapezoidalSampler(int _row = 2, int _col = 2) : row(_row), col(_col) {}

    virtual Vector2 Sample(int x, int y) override;
};

Vector2 TrapezoidalSampler::Sample(int x, int y) {

    int sx = index % 2;
    int sy = index / 2;

    double r1 = 2 * random.RandomDouble();
    double r2 = 2 * random.RandomDouble();

    double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    double s = static_cast<double>(x) + (dx + sx + 0.5) / 2;
    double t = static_cast<double>(y) + (dy + sy + 0.5) / 2;

    return {s, t};
}