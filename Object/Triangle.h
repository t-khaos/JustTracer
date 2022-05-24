#pragma once

#include "../Common/Object.h"

struct Triangle : Object {


    union {
        Vector3d vertices[3];
        struct {
            Vector3d A, B, C;
        };
    };

    Vector3d normal;
    double area;

    //三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
    Triangle(Vector3d _v0, Vector3d _v1, Vector3d _v2);


    virtual bool Intersect(const Ray &ray, HitResult &result, double t_near) const override;
};