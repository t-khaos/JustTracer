#pragma once

#include "../Tool/Vector3.h"

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

struct EnvLight{

};