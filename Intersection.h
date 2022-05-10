#pragma once

#include "Math/Vector3.h"

struct Frame{
    Vector3 t,b,n;

    Frame(Vector3& _n):n(_n.normalize()){
        Vector3 temp = std::abs(n.x)>0.99?Vector3(0,1,0):Vector3(1,0,0);
        t = n.cross(temp).normalize();
        b = t.cross(n).normalize();
    }

    Vector3 ToWorld(const Vector3& vector){
        return t*vector.x+b*vector.y+n*vector.z;
    }

    Vector3 ToLocal(const Vector3& vector){
        return {t.dot(vector), b.dot(vector), n.dot(vector)};
    }
};


struct BSDFSample{
    Color radiance;
    Vector3 wi;
    double pdf;
};


struct BSDF{

};

struct Intersection {
    Point3 point;
    Vec3 normal;
    Color emission;

    Color Le;
};
