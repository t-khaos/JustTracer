#pragma once

#include "../Math/Vector.h"

struct LightResult{
    Color emission;
    Vector3 normal;
    Point3 point;
    float pdf;

    LightResult(): emission(Color()), normal(Vector3()), pdf(0.0f){}
};