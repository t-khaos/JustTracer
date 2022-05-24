
#include "TrapezoidalSampler.h"

Vector2d TrapezoidalSampler::CastRayByDistribution(int x, int y) {
    index = index >= 4 ? 0 : index;

    int sx = index % 2;
    int sy = index / 2;

    double r1 = 2 * RandomDouble();
    double r2 = 2 * RandomDouble();

    double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

    double s = static_cast<double>(x) + (dx + sx + 0.5) / 2;
    double t = static_cast<double>(y) + (dy + sy + 0.5) / 2;

    index++;

    return Vector2d(s, t);
}