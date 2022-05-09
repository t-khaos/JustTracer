#pragma once

#include <memory>
#include <vector>

#include "Sphere.hpp"

struct Scene{

    int width;
    int height;

    std::vector<std::shared_ptr<Object>> objects;

    Scene(int _w, int _h):width(_w),height(_h){};
    void add(std::shared_ptr<Object> object){objects.push_back(object);}

    bool intersect(const Ray& ray, HitResult& result) const;
    Color cast_ray(const Ray& ray) const;

};

bool Scene::intersect(const Ray &ray, HitResult &result) const {
    HitResult tempResult;
    bool isHit = false;
    double time_closest = std::numeric_limits<double>::max();
    double eps = 0.0001;

    for(auto& object : objects){
        if(object->intersect(ray, tempResult, eps, time_closest)){
            isHit = true;
            time_closest = tempResult.time;
            result = tempResult;
        }
    }
    return isHit;
}

Color Scene::cast_ray(const Ray& ray) const{
    HitResult result;
    if(intersect(ray, result)){
        return 0.5 * (result.normal + Color(1.0));
    }
    auto t = 0.5*(ray.direction.y + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}