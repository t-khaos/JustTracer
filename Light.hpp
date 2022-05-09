#pragma once

#include "Vector.hpp"

enum LightType{
    Area,
    Env
};

struct Light{
    LightType type;
    Color radiance;
    Vector3 position;
};

struct AreaLight : Light{


    Color Le(){

    }
};

struct PointLight{

};

struct DirectionLight{
    
};