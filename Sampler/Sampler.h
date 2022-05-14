#pragma once


#include <vector>
#include <iostream>
#include "../Tool/Vector2.h"


struct Sampler{
    virtual Vec2 CastRayByDistribution(int x, int y) = 0;
};
