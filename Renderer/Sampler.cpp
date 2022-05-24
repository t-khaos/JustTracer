


#include "Sampler.h"
#include "../Math/Random.h"

Vector2d Sampler::CastRayByDistribution(int x, int y) {
    double s = x, t = y;

    if(type == SamplerType::Trapezoidal){
        index = index >= 4 ? 0 : index;

        int sx = index % 2;
        int sy = index / 2;

        double r1 = 2 * RandomDouble();
        double r2 = 2 * RandomDouble();

        double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
        double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

        s = static_cast<double>(x) + (dx + sx + 0.5) / 2;
        t = static_cast<double>(y) + (dy + sy + 0.5) / 2;

        index++;
    }
    else if(type == SamplerType::Uniform){
        s = static_cast<double>(x) + RandomDouble();
        t = static_cast<double>(y) + RandomDouble();
    }

    return Vector2d(s, t);
}