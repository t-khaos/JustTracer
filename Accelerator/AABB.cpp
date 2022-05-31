
#include "AABB.h"

bool AABB::Intersect(const Ray &ray, float t_near) {
    Vector3 invDirection = 1.0f / ray.direction;

    Vector3 t0 = (minVector - ray.origin) * invDirection;
    Vector3 t1 = (maxVector - ray.origin) * invDirection;

    Vector3 t_min = MinVector(t0, t1);
    Vector3 t_max = MaxVector(t0, t1);

    float t_enter = MaxValue(t_min);
    float t_exit = MinValue(t_max);

    //射线与包围盒不相交
    if(t_enter>t_exit+0.00016f | t_exit < 0.0f)
        return false;

    //射线已经和别的包围盒相交
    if(t_enter < t_near)
        return false;

    return true;
}