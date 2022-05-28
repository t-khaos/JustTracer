#pragma once

#include "../Math/Vector.h"

struct BxDFResult {
    Vector3 direction;
    float pdf;
    Color fr;
    bool isDelta;

    BxDFResult(Vector3 _dir, float _pdf, Color _fr, bool _flag)
            : direction(_dir), pdf(_pdf), fr(_fr), isDelta(_flag) {}
};