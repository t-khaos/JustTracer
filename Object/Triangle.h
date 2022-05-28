#pragma once

#include "../Common/Object.h"

struct Triangle : Object {


    union {
        Vector3 vertices[3];
        struct {
            Vector3 A, B, C;
        };
    };

    Vector3 normal;
    float area;
    std::shared_ptr<Material> material;

    //三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
    Triangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, std::shared_ptr<Material> _mat);


    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;
};