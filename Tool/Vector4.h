#pragma once

#include "Vector3.h"

struct Vector4{
    union{
        struct {
            double x,y,z,w;
        };
        double data[4];
    };

    Vector4():data{0,0,0,0}{}
    Vector4(double _x,double _y,double _z,double _w):data{_x,_y,_z,_w}{}
    Vector4(Vector3 _v):data{_v.x,_v.y,_v.z,1}{}

};

typedef Vector4 Vec4;