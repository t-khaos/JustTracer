#pragma once


#include "Light.h"

struct SphereLight : Light{
    std::shared_ptr<Sphere> sphere;

    SphereLight(std::shared_ptr<Sphere> _shape) : sphere(_shape) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;

};

inline void SphereLight::Sample(HitResult &result) {

    float theta = 2.0 * PI * RandomFloat();
    float phi = PI * RandomFloat();
    Vector3f direction(
            std::cos(phi),
            std::sin(phi) * std::cos(theta),
            std::sin(phi) * std::sin(theta)
    );

    result.point = sphere->center + direction * sphere->radius;
    result.normal = direction;
    result.material = sphere->material;
}

inline float SphereLight::PDF() {
    return 1 / (4 * PI * sphere->radius * sphere->radius);
}