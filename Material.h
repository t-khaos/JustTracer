#pragma once




enum MaterialType{
    PBR_COOK_TORRANCE,
};

struct Material{
    MaterialType type;
};

struct PBRMaterial : Material{

};