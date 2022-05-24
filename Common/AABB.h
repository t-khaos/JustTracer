#pragma once


#include "../Math/Vector.h"
#include "Global.h"
#include "Object.h"

struct AABB{
    Vector3d minVector, maxVector;

    AABB(Vector3d _min = MIN_DOUBLE, Vector3d _max = MAX_DOUBLE)
        :minVector(_min),maxVector(_max){}
};