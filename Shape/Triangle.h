#pragma once

#include <vector>
#include "../Tool/Vector.h"
#include "Object.h"


struct Rectangle : Object {
    union {
        Vector3f vertices[4];
        struct {
            Vector3f A, B, C, D;
        };
    };

    Vector3f normal;
    float area;
    Vector3f s, t;
    std::shared_ptr<Material> material;

    Rectangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Vector3f _v3, std::shared_ptr<Material> _mat)
            : A(_v0), B(_v1), C(_v2), D(_v3), material(_mat) {
        s = B - A;
        t = D - A;
        normal = Normalize(Cross(s, t));
        area = Norm(Cross(s, t));
    }

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;

};


inline bool Rectangle::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    if (Dot(-ray.direction, normal) < EPSILON)
        return false;

    float time = Dot((A - ray.origin), normal) * (1 / Dot(ray.direction, normal));

    if (time <= 0.f || time > t_near)
        return false;

    Point3f point = ray.at(time);

    //矩形在xyz轴上取值范围
    auto maxVector = MaxVector(MaxVector(A, B), MaxVector(C, D));
    auto minVector = MinVector(MinVector(A, B), MinVector(C, D));
    if (minVector.x - point.x > EPSILON || point.x - maxVector.x > EPSILON ||
        minVector.y - point.y > EPSILON || point.y - maxVector.y > EPSILON ||
        minVector.z - point.z > EPSILON || point.z - maxVector.z > EPSILON)
        return false;

    result.distance = time;
    result.point = point;
    result.normal = normal;
    result.material = material;

    return true;
}


struct Triangle : Object {


    union {
        Vector3f vertices[3];
        struct {
            Vector3f A, B, C;
        };
    };

    Vector3f normal;
    float area;

    //三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2)
            : A(_v0), B(_v1), C(_v2) {
        Vector3f AB, AC;
        AB = B - A;
        AC = C - A;
        normal = Normalize(Cross(AB, AC));

        // 三维空间中三角形面积为两边叉积的取模乘以二分之一
        // 1/2 * |AB x AC|
        area = Norm(Cross(AB, AC)) * 0.5f;
    }


    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;

};

inline bool Triangle::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    if (Dot(-ray.direction, normal) < EPSILON)
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

    //      det([S E1 E2])        det([-D S E2])        det([-D E1 S])
    // t = ----------------, α = ----------------, β = -----------------
    //      det([-D E1 E2])       det([-D E1 E2])       det([-D E1 E2])

    // 将行列式转换为标量三重积形式
    //      (S × E1) · E2     (S × E1) · E2  --> 按照行列式顺序，叉乘和点乘前后可以调换
    // t = --------------- = ---------------
    //      -D · (E1 × E2)    E1 · (D × E2)  --> 改变行列式顺序，做初等变换，消掉负号

    //                                     S2 · E2
    // 令 S1 = D × E2, S2 = S × E1, 则 t = ---------
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
    //  [α] = -------  [S1 · S ]
    //  [β]   S1 · E1  [S2 · D ]

    // 代码实现
    Vector3f D = ray.direction;
    Vector3f S = ray.origin - A;
    Vector3f E1 = B - A, E2 = C - A;
    Vector3f S1 = Cross(D, E2);
    Vector3f S2 = Cross(S, E1);

    float division = 1 / Dot(S1, E1);

    float time = Dot(S2, E2) * division;
    float alpha = Dot(S1, S) * division;
    float beta = Dot(S2, D) * division;

    //如果 γ 特别小可能会出现浮点数精度误差导致 1 - alpha - beta 小于0
    if (time <= 0.f || alpha < 0.f || beta < 0.f || (1 - alpha - beta) < -EPSILON)
        return false;

    //如果时间大于了最大时间，说明已经再碰到该三角形之前已经碰撞到了别的三角形
    if (time > t_near)
        return false;

    result.distance = time;
    result.point = alpha * A + beta * B + (1 - alpha - beta) * C;
    result.normal = normal;
    return true;
}


struct Mesh : Object {
    std::vector<std::shared_ptr<Triangle>> triangles;
    std::shared_ptr<Material> material;

    Mesh(const std::shared_ptr<Material> &_mat)
            : material(_mat) {}

    virtual bool Intersect(const Ray &ray, HitResult &result, float t_near) const override;

    void AddTriangle(const std::shared_ptr<Triangle> &triangle) { triangles.push_back(triangle); }

    float TotalArea();

};

float Mesh::TotalArea() {
    float sum = 0.f;
    for (auto &triangle: triangles)
        sum += triangle->area;
    return sum;
}

bool Mesh::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    HitResult tempResult;
    bool isHit = false;
    float closestTime = t_near;

    for (auto &triangle: triangles) {
        if (triangle->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = result.distance;
            result = tempResult;
            result.material = material;
        }
    }
    return isHit;
}
