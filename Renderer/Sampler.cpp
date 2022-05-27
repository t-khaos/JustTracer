


#include "Sampler.h"
#include "../Math/Random.h"

Vector2 Sampler::CastRayByDistribution(int x, int y) {
    float s = x, t = y;

    if(type == SamplerType::Trapezoidal){
        index = index >= 4 ? 0 : index;

        int sx = index % 2;
        int sy = index / 2;

        float r1 = 2 * RandomFloat();
        float r2 = 2 * RandomFloat();

        float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
        float dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

        s = static_cast<float>(x) + (dx + sx + 0.5) / 2;
        t = static_cast<float>(y) + (dy + sy + 0.5) / 2;

        index++;
    }
    else if(type == SamplerType::Uniform){
        s = static_cast<float>(x) + RandomFloat();
        t = static_cast<float>(y) + RandomFloat();
    }

    return Vector2(s, t);
}