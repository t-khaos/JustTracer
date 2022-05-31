
#include "AABB.h"

bool AABB::Intersect(const Ray &ray, float t_near) {

    Vector3 invDirection = 1.0f / ray.direction;
    Vector3 t0 = (minVector - ray.origin) * invDirection;
    Vector3 t1 = (maxVector - ray.origin) * invDirection;

    Vector3 t_min = MinVector(t0, t1);
    Vector3 t_max = MaxVector(t0, t1);

    float t_enter = MaxValue(t_min);
    float t_exit = MinValue(t_max);

    return t_enter <= t_exit && t_exit > 0;
}