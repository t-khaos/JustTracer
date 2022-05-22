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


    std::shared_ptr<Material> material;

    //三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2) : A(_v0), B(_v1), C(_v2) {
        AB = B - A;
        AC = C - A;
        normal = Normalize(Cross(AB, AC));

        // 三维空间中三角形面积为两边叉积的取模乘以二分之一
        // 1/2 *|AB x AC|
        area = Norm(Cross(AB, AC)) * 0.5f;
    }


    virtual bool intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const override;

    float PDF();

};

inline float Triangle::PDF() {
    return 1 / area;
}

inline bool Triangle::intersect(const Ray &ray, HitResult &result, float t_min, float t_max) const {
    if (Dot(ray.direction, normal) > 0)
        return false;

    // Möller-Trumbore Algorithm

    // 光线在 t 时刻一点 = 三角形重心坐标一点
    // O + tD = α * A + β * B + (1 - α - β) * C
    // O + tD = α * A + β * B + C - α * C - β * C
    // O - C  = α * (A - C) + β * (B - C) - tD

    // 令 S = O - C, E1 = A - C, E2 = B - C
    // -tD + α * E1 + β * E2 = S
    //              [ t ]
    // [-D E1 E2] * [ α ] = S
    //              [ β ]

    // 根据克拉默法则可得

    //      |S E1 E2|          |-D S E2|        |-D E1 S|
    // t = ------------, α =  -----------, β = -----------
    //      |-D E1 E2|         |-D E1 E2|       |-D E1 E2|

    // 将行列式转换为标量三重积形式
    //      (S × E1) · E2     (S × E1) · E2 //按照行列式顺序，叉乘和点乘可以调换
    // t = --------------- = ---------------
    //      -D · (E1 × E2)    E1 · (D × E2) //初等变换消掉负号消掉负号

    //                                     S2 · E2
    // 令 S1 = D × E2, S2 = S × E1, 则 t = ---------
    //
    //                                     E1 · S1
    //同理可得
    //      -D · (S × E2)     S · (D × E2)      S · S1
    // α = --------------- = --------------- = --------
    //      -D · (E1 × E2)    E1 · (D × E2)     E1 · S1

    //      -D · (E1 × S)     D · (S × E1)      D · S2
    // β = --------------- = --------------- = --------
    //      -D · (E1 × E2)    E1 · (D × E2)     E1 · S1

    // 整理可得
    //  [t]      1     [S2 · E2]
    //  [α] = -------  [S1 · S]
    //  [β]   S1 * E1  [S2 · D]

    // 代码实现
    auto S = ray.origin - A;
    auto E1 = AB, E2 = AC;
    auto S1 = Cross(ray.direction, E2);
    auto S2 = Cross(S, E1);

    auto division = 1 / Dot(S1, E1);

    auto time = Dot(S2, E2) * division;
    auto alpha = Dot(S1, S) * division;
    auto beta = Dot(S2, ray.direction) * division;

    //如果γ特别小可能会出现浮点数精度误差导致 1 - alpha - beta 小于0
    if (time <= 0.f || alpha < 0.f || beta < 0.f || (1 - alpha - beta) < -EPSILON)
        return false;

    //如果时间大于了最大时间，说明已经再碰到该三角形之前已经碰撞到了别的三角形
    if(time > t_max)
        return false;

    result.distance = time;
    result.point = alpha * A + beta * B + (1-alpha-beta) * C;
    result.normal = normal;
    result.material = material;
}
