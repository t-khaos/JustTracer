#pragma once


#include "Object.h"
#include "Vector.h"


struct Sphere : Object{

    double radius;
    Vec3 position;

    Sphere(const double _r, const Vec3 _p):radius(_r), position(_p){}

    bool intersect(const Ray& ray, HitResult& result, double t_min, double t_max)const override;
};


bool Sphere::intersect(const Ray& ray, HitResult& result, double t_min, double t_max)const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vec3 op = ray.origin - position;
    //h=b/2
    double h = op.dot(ray.direction);
    double det = h*h-op.dot(op)+radius*radius;

    if(det<0)
    return false;

    det= sqrt(det);

    double root =  -h - det;
    if(root<t_min || root>t_max) {
    root = -h + det;
    if(root<t_min || root>t_max)
    return false;
    }

    result.time = root;
    result.point = ray.at(result.time);
    result.normal = (result.point - position).normalize();
    double NoL= result.normal.dot(ray.direction);
    result.normal = NoL<0?result.normal:-result.normal;

    return true;
}