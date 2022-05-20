#pragma once

#include "Vector3.h"

struct Vector4{
    union{
        struct {
            float x,y,z,w;
        };
        float data[4];
    };

    Vector4():data{0,0,0,0}{}
    Vector4(float _x,float _y,float _z,float _w):data{_x,_y,_z,_w}{}
    Vector4(Vector3 _v):data{_v.x,_v.y,_v.z,1}{}

};

typedef Vector4 Vec4;