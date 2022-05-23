
#include "Rectangle.h"

bool Rectangle::Intersect(const Ray &ray, HitResult &result, float t_near) const {
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

void Rectangle::SampleHitResult(HitResult &result) {
    //矩形内均匀采样
    result.point = A + s * RandomFloat() + t * RandomFloat();
    result.material = material;
    result.normal = normal;
}


float Rectangle::PDF() {
    return 1 / area;
}