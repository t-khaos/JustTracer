#pragma once

#include "../Math/Vector.h"
#include "../Math/Global.h"

//最大的维度
enum class Dimension {
    X, Y, Z, W
};

struct AABB {
    Vector3d minVector, maxVector;

    AABB() : minVector(MIN_DOUBLE), maxVector(MAX_DOUBLE) {}

    AABB(Vector3d _min, Vector3d _max)
            : minVector(_min), maxVector(_max) {}

    AABB(Vector3d _cen)
            : minVector(_cen), maxVector(_cen) {}

    AABB(const AABB &other)
            : minVector(other.minVector), maxVector(other.maxVector) {}

    Vector3d Centroid() {
        return (maxVector + minVector) * 0.5;
    }


};

inline Dimension MaxDimension(const AABB &box) {
    auto diagonal = box.maxVector - box.minVector;
    if (diagonal.x > diagonal.y && diagonal.x > diagonal.z)
        return Dimension::X;
    else if (diagonal.y > diagonal.x)
        return Dimension::Y;
    else
        return Dimension::Z;
}

inline AABB MergeBounds(const AABB &box, const AABB &other) {
    return AABB(
            MinVector(box.minVector, other.minVector),
            MaxVector(box.maxVector, other.maxVector)
    );
}