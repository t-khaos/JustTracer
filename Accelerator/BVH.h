#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "AABB.h"
#include "../Common/Object.h"

struct BVHNode {
    AABB bounds;
    std::shared_ptr<BVHNode> left = nullptr;
    std::shared_ptr<BVHNode> right = nullptr;
    std::shared_ptr<Object> object = nullptr;

    BVHNode(): bounds(AABB()){}
};

struct BVH {

    std::shared_ptr<BVHNode> root;
    std::vector<std::shared_ptr<Object>> objects;

    BVH(const std::vector<std::shared_ptr<Object>> &_objs)
    : objects(_objs),root(std::make_shared<BVHNode>()) {}

    std::shared_ptr<BVHNode> Build(std::vector<std::shared_ptr<Object>> objs);

    bool Intersect(const Ray &ray, std::shared_ptr<BVHNode> node, HitResult& result);
};