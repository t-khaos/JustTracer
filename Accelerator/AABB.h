#pragma once

#include "../Math/Vector.h"
#include "../Math/Global.h"
#include "../Common/Ray.h"
#include "../Common/HitResult.h"

//最大的维度
enum class Dimension {
    X, Y, Z, W
};

struct AABB {
    Vector3 minVector, maxVector;

    AABB() : minVector(MIN_FLOAT), maxVector(MAX_FLOAT) {}

    AABB(Vector3 _min, Vector3 _max) : minVector(_min), maxVector(_max) {}

    AABB(Vector3 _cen) : minVector(_cen), maxVector(_cen) {}

    AABB(const AABB &other) : minVector(other.minVector), maxVector(other.maxVector) {}

    Vector3 Centroid() { return (maxVector + minVector) * 0.5f;}

    bool Intersect(const Ray &ray, float t_near);

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