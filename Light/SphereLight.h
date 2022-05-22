#pragma once

#include "../Tool/Vector.h"
#include "../Shape/Object.h"
#include "../Shape/Triangle.h"


struct LightSampleResult {
    float PDF;
    Point3f position;
};

struct Light{
    virtual void Sample(HitResult &result) = 0;
    virtual float PDF() = 0;
};

struct AreaLight : Light{
    std::shared_ptr<std::vector<Triangle>> triangles;
    AreaLight(std::shared_ptr<std::vector<Triangle>> _triangles) : triangles(_triangles) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;
};


struct SphereLight : Light{
    std::shared_ptr<Sphere> sphere;

    SphereLight(std::shared_ptr<Sphere> _shape) : sphere(_shape) {}

    virtual void Sample(HitResult &result) override;

    virtual float PDF() override;

};

inline float SphereLight::PDF() {
    return sphere->PDF();
}

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