#pragma once

#include <memory>

#include "Ray.hpp"

struct Object{
    Object(){}
    virtual bool intersect(const Ray& ray, HitResult& result, double t_min, double t_max)const=0;
};