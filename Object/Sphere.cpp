
#include "Sphere.h"

Sphere::Sphere(const float _r, const Vector3 _p, std::shared_ptr<Material> _mat)
        : radius(_r), center(_p), material(_mat) {

    //构建包围盒
    bounds = AABB(
            center - Vector3(radius, radius, radius),
            center + Vector3(radius, radius, radius)
    );
}

bool Sphere::Intersect(Ray &ray, HitResult &result, float t_near) const {
    //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    Vector3 op = ray.origin - center;
    //h=b/2
    float h = Dot(op, ray.direction);
    float det = h * h - Dot(op, op) + radius * radius;
    if (det < 0)
        return false;
    det = sqrt(det);
    float time = -h - det;
    if (time < EPSILON || time > t_near) {
        time = -h + det;
        if (time < EPSILON || time > t_near)
            return false;
    }
    result.time = time;
    result.point = ray.at(time);
    result.normal = Normalize(result.point - center);
    float NoL = Dot(result.normal, ray.direction);
    result.normal = NoL < 0 ? result.normal : -result.normal;
    result.material = material;
    result.isLight = material->type == MaterialType::Light;
    return true;
}

void Sphere::SampleLight(LightResult &result) {
    //球体表面均匀采样
    //天顶角 arccos(1-2r1)或2*arccos(sqrt(1-r1))
    //方位角 2*PI*r2
    float theta = 2 * PI * RandomFloat();
    float phi = std::acos(1.0f - 2 * RandomFloat());
    Vector3 direction(
            std::cos(phi),
            std::sin(phi) * std::cos(theta),
            std::sin(phi) * std::sin(theta)
    );

    result.point = center + direction * radius;
    result.normal = direction;
    result.emission = material->emission;
    result.pdf = PDF();

}

float Sphere::PDF() {
    return 1 / (4 * PI * radius * radius);
}