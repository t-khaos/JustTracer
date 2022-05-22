#pragma once

#include <vector>
#include "../Tool/Vector.h"
#include "Object.h"

struct Triangle : Object {
    union {
        Vector3f vertices[3];
        struct {
            Vector3f A, B, C;
        };
    };

    Vector3f AB, AC;
    Vector3f normal;
    float area;

    //三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2) : A(_v0), B(_v1), C(_v2) {
        AB = B - A;
        AC = C - A;
        normal = Normalize(Cross(AB,AC));

        // 三维空间中三角形面积为两边叉积的取模乘以二分之一
        // 1/2 *|AB x AC|
        area =  Norm(Cross(AB,AC))*0.5f;
    }


    virtual bool intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const override;

};


inline bool Triangle::intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const {

}
