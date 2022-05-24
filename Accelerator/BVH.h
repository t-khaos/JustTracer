#pragma once

#include <memory>
#include <vector>
#include "AABB.h"
#include "../Common/Object.h"

enum BVHSplitMethod {
    NAIVE,
    SAH
};

struct BVHNode {
    AABB bounds;
    std::shared_ptr<BVHNode> left = nullptr;
    std::shared_ptr<BVHNode> right = nullptr;
    std::shared_ptr<Object> object = nullptr;

    BVHNode(): bounds(AABB()){}
};

struct BVH {

    std::vector<std::shared_ptr<Object>> objects;

    BVH(const std::vector<std::shared_ptr<Object>> &_objs) : objects(_objs) {}

    std::shared_ptr<BVHNode> Build(std::vector<std::shared_ptr<Object>> objs);

    bool Intersect(const Ray &ray);
};

std::shared_ptr<BVHNode> BVH::Build(std::vector<std::shared_ptr<Object>> objs) {

    auto node = std::make_shared<BVHNode>();
    //获取当前节点的边界
    AABB bounds;
    for (auto &obj: objs) {
        MergeBounds(bounds, obj->bounds);
    }

    if (objs.size() == 1) {
        node->bounds = objs[0]->bounds;
        node->object = objs[0];
        node->left = nullptr;
        node->right = nullptr;

        return node;
    } else if (objs.size() == 2) {
        node->left = Build(std::vector{objs[0]});
        node->right = Build(std::vector{objs[1]});

        node->bounds = MergeBounds(
                node->left->bounds,
                node->right->bounds
        );
        return node;
    }
    else{
        //依据物体包围盒的质心，对物体进行排序
        AABB centroidBounds;

        for(auto obj:objs)
            centroidBounds = MergeBounds(centroidBounds, AABB(obj->bounds.Centroid()));

        //根据质心包围盒的对角线的三维长短选择按那个维度进行排序
        switch (MaxDimension(centroidBounds)) {
            case Dimension::X:
                break;
            case Dimension::Y:
                break;
            case Dimension::Z:
                break;
        }
    }
}

