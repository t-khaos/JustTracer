
#include "Rectangle.h"
#include "../Math/Random.h"

Rectangle::Rectangle(Vector3 _v0, Vector3 _v1, Vector3 _v2, Vector3 _v3, std::shared_ptr<Material> _mat)
        : A(_v0), B(_v1), C(_v2), D(_v3), material(_mat) {
    s = B - A;
    t = D - A;
    normal = Normalize(Cross(s, t));
    area = Norm(Cross(s, t));

    //构建包围盒
    bounds = AABB(
            MinVector(MinVector(A, B), MinVector(C, D)),
            MaxVector(MaxVector(A, B), MaxVector(C, D))
    );
}

bool Rectangle::Intersect(const Ray &ray, HitResult &result, float t_near) const {
    if (Dot(-ray.direction, normal) < EPSILON)
        return false;

    float time = Dot((A - ray.origin), normal) * (1 / Dot(ray.direction, normal));

    if (time <= 0.f || time > t_near)
        return false;

    Point3 point = ray.at(time);

    //矩形在xyz轴上取值范围
    if (bounds.minVector.x - point.x > EPSILON || point.x - bounds.maxVector.x > EPSILON ||
        bounds.minVector.y - point.y > EPSILON || point.y - bounds.maxVector.y > EPSILON ||
        bounds.minVector.z - point.z > EPSILON || point.z - bounds.maxVector.z > EPSILON)
        return false;

    result.time = time;
    result.point = point;
    result.normal = normal;
    result.material = material;
    result.isLight = material->type == MaterialType::Light;

    return true;
}

void Rectangle::SampleHitResult(HitResult &result) {
    //矩形内均匀采样
    result.point = A + s * RandomFloat() + t * RandomFloat();
    result.material = material;
    result.normal = normal;
}


float Rectangle::PDF() {
    return 1 / area;
}