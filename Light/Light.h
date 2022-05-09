#pragma once

#include "../Math/Vector3.h"

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