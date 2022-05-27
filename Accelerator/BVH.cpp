
#include "BVH.h"

bool BVH::Intersect(const Ray &ray, std::shared_ptr<BVHNode> node, HitResult& result){
    return false;
}

std::shared_ptr<BVHNode> BVH::Build(std::vector<std::shared_ptr<Object>> objs) {

    auto node = std::make_shared<BVHNode>();

    if (objs.size() == 1) {
        //设置左右子节点和边界
        node->bounds = objs[0]->bounds;
        node->object = objs[0];
        node->left = nullptr;
        node->right = nullptr;

        return node;
    } else if (objs.size() == 2) {
        //设置左右子节点和边界
        node->left = Build(std::vector{objs[0]});
        node->right = Build(std::vector{objs[1]});

        node->bounds = MergeBounds(
                node->left->bounds,
                node->right->bounds
        );
        return node;
    }
    else{
        //依据物体包围盒的质心坐标构建包围盒
        AABB centroidBounds;
        for(auto obj:objs)
            centroidBounds = MergeBounds(centroidBounds, AABB(obj->bounds.Centroid()));

        //得出质心包围盒的对角线，选取跨度最长的维度
        //一句包围盒内的物体质心坐标按指定维度排序
        switch (MaxDimension(centroidBounds)) {
            case Dimension::X:
                std::sort(objs.begin(),objs.end(), [](std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2){
                    return obj1->bounds.Centroid().x < obj2->bounds.Centroid().x;
                });
                break;
            case Dimension::Y:
                std::sort(objs.begin(),objs.end(), [](std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2){
                    return obj1->bounds.Centroid().y < obj2->bounds.Centroid().y;
                });
                break;
            case Dimension::Z:
                std::sort(objs.begin(),objs.end(), [](std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2){
                    return obj1->bounds.Centroid().z < obj2->bounds.Centroid().z;
                });
                break;
        }

        //排序后平分数组
        auto begin = objs.begin();
        auto mid = objs.begin() + (objs.size()/2);
        auto end = objs.end();

        auto leftObjs = std::vector<std::shared_ptr<Object>>(begin,mid);
        auto rightObjs = std::vector<std::shared_ptr<Object>>(mid,end);

        assert(objs.size() == (leftObjs.size()+rightObjs.size()));

        //设置左右子节点和边界
        node->left = Build(leftObjs);
        node->right = Build(rightObjs);
        node->bounds = MergeBounds(node->left->bounds, node->right->bounds);

        return node;
    }
}