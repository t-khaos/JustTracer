#pragma once


#include <memory>
#include "AABB.h"

enum BVHSplitMethod{
    NAIVE,
    SAH
};

struct BoundsNode{
    AABB bounds;
    std::shared_ptr<BoundsNode> left;
    std::shared_ptr<BoundsNode> right;
    std::shared_ptr<Object> object;
};

struct BVH{

    std::vector<std::shared_ptr<Object>> objects;

    BVH(const std::vector<std::shared_ptr<Object>>& _objs):objects(_objs){}

    void BuildTree();

    bool Intersect(const Ray& ray);
};

void BVH::BuildTree(){
    Vector3d minVector(MIN_DOUBLE);
    Vector3d maxVector(MAX_DOUBLE);
    for(auto object : objects){

    }
}