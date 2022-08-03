
#include <vector>

#include "Triangle.h"

//三角形顶点规定要以逆时针顺序旋转，统一叉乘矢量向上
Triangle::Triangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, std::shared_ptr<Material> _mat)
        : A(_v0), B(_v1), C(_v2),material(_mat) {
    Vector3 AB, AC;
    AB = B - A;
    AC = C - A;
    normal = Normalize(Cross(AB, AC));

    // 三维空间中三角形面积为两边叉积的取模乘以二分之一
    // 1/2 * |AB x AC|
    area = Norm(Cross(AB, AC)) * 0.5;

    //构建包围盒
    bounds = AABB(
            MinVector(MinVector(A, B), C),
            MaxVector(MaxVector(A, B), C)
    );
}

bool Triangle::Intersect(Ray &ray, HitResult &result, float t_near) const {
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

    // 同理可得
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
    Vector3 D = ray.direction;
    Vector3 S = ray.origin - A;
    Vector3 E1 = B - A, E2 = C - A;
    Vector3 S1 = Cross(D, E2);
    Vector3 S2 = Cross(S, E1);

    float denom = Dot(S1, E1);

    float time = Dot(S2, E2) / denom;
    float alpha = Dot(S1, S) / denom;
    float beta = Dot(S2, D) / denom;

    if (time <= 0.f || time >= t_near || alpha < 0.f || beta < 0.f || (alpha + beta) > 1.0f)
        return false;

    result.time = time;
    result.point = alpha * A + beta * B + (1 - alpha - beta) * C;
    result.normal = normal;
    result.material = material;
    result.isLight = material->type == MaterialType::Light;
    return true;
}


struct Mesh : Object {
    std::vector<std::shared_ptr<Triangle>> triangles;
    std::shared_ptr<Material> material;

    Mesh(std::shared_ptr<Material> _mat)
            : material(_mat) {}

    virtual bool Intersect(Ray &ray, HitResult &result, float t_near) const override;

    void AddTriangle(std::shared_ptr<Triangle> triangle) { triangles.push_back(triangle); }

    float TotalArea();

};

float Mesh::TotalArea() {
    float sum = 0.f;
    for (auto &triangle: triangles)
        sum += triangle->area;
    return sum;
}

bool Mesh::Intersect(Ray &ray, HitResult &result, float t_near) const {
    HitResult tempResult;
    bool isHit = false;
    float closestTime = t_near;

    for (auto &triangle: triangles) {
        if (triangle->Intersect(ray, tempResult, closestTime)) {
            isHit = true;
            closestTime = result.time;
            result = tempResult;
            result.material = material;
        }
    }
    return isHit;
}
