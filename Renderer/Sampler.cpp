


#include "Sampler.h"
#include "../Math/Random.h"

Vector2 Sampler::CastRayByDistribution(int x, int y)
{
    Vector2 point;
    if (type == SamplerType::Trapezoidal)
    {
        index = index >= 4 ? 0 : index;

        int sx = index % 2;
        int sy = index / 2;

        float r1 = 2 * RandomFloat();
        float r2 = 2 * RandomFloat();

        float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
        float dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

        point.x = static_cast<float>(x) + (dx + static_cast<float>(sx) + 0.5f) / 2.0f;
        point.y = static_cast<float>(y) + (dy + static_cast<float>(sy) + 0.5f) / 2.0f;

        index++;
    }
    else if (type == SamplerType::Uniform)
    {
        point.x = static_cast<float>(x) + RandomFloat();
        point.y = static_cast<float>(y) + RandomFloat();
    }
    else if (type == SamplerType::Disk)
    {
        auto radius = 2 * sqrt(static_cast<float>(RandomFloat()));
        auto angle = static_cast<float>(RandomFloat()) * PI * 2.0f;
        point.x = static_cast<float>(x) + 0.5f + radius * std::cos(angle);
        point.y = static_cast<float>(y) + 0.5f + radius * std::sin(angle);
    }
    return point;
}