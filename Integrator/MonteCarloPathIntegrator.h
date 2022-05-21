#pragma once

#include "PathIntegrator.h"


struct MonteCarloPathIntegrator : PathIntegrator {
    float P_RR = 0.8;

    MonteCarloPathIntegrator(int _depth = 5) : PathIntegrator(_depth) {}

    virtual Color3f Li(const Ray &ray, std::shared_ptr<Scene> scene) override;

    virtual Color3f CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) override;
};

Color3f MonteCarloPathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}

Color3f MonteCarloPathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    //递归超过指定层数结束
    if (depth >= depth_max)
        return Color3f(0.f);
    //光线与场景求交
    HitResult result;
    if (!scene->Intersect(ray, result))
        return Color3f(0.f);
    //击中光源
    if (result.material->type == MaterialType::LIGHT)
        return result.material->emission;
    //击中物体
    Vector3f L_direct, L_indirect;
    HitResult sampleLightResult;
    //1.对光源采样，获取采样pdf，在光源表面均选取采样的位置
    float pdf_light = scene->lights[0]->PDF();
    scene->lights[0]->Sample(sampleLightResult);
    //交点与采样点方向
    Vector3f toLightDir = sampleLightResult.point - result.point;
    Vector3f toLightDirN = Normalize(toLightDir);
    float distance = Length(toLightDir);
    //生成光线，向该方向投射，获取与光源交点的信息
    Ray toLightRay(result.point, toLightDirN);
    HitResult toLightResult;
    scene->Intersect(toLightRay, toLightResult);

    if (toLightResult.distance - distance > -EPSILON) {
        //L_dir = L_i * Eval * cos_theta * cos_theta_x / | x - p | ^ 2 / pdf_light
        L_direct = sampleLightResult.material->emission //光源自发光项
                   * result.material->Eval(ray.direction, toLightDirN, result.normal)
                   * Dot(toLightDirN, result.normal) //光线方向与物体交点的夹角余弦
                   * Dot(-toLightDirN, sampleLightResult.normal)//-光线方向与光源交点的夹角余弦
                   / (distance * distance)//光照强度随距离的平方减弱
                   / pdf_light;
    }
    //建议至少3次递归再进行轮盘赌
    if (depth > 3 && RandomFloat() > P_RR)
        return L_direct;
    //2.对交点采样，随机采样漫反射方向
    Vector3f diffuseDir = result.material->Sample(ray.direction, result.normal);
    Vector3f diffuseDirN = Normalize(diffuseDir);
    //生成光线，向该方向投射
    Ray diffuseRay(result.point, diffuseDirN);
    HitResult diffuseResult;
    //是否击中物体
    if (!scene->Intersect(diffuseRay, diffuseResult))
        return L_direct;
    //击中的物体是否为光源
    if (diffuseResult.material->type == MaterialType::LIGHT)
        return L_direct;
    //击中物体则继续递归
    //获取交点材质的pdf
    float pdf = result.material->PDF(ray.direction, diffuseDirN, result.normal);
    // CastRay() * Eval() * cos_theta / P_RR / pdf;
    L_indirect = CastRay(diffuseRay, scene, ++depth)
                 * result.material->Eval(ray.direction, diffuseDirN, result.normal)
                 * (Dot(diffuseDirN, result.normal))
                 / P_RR
                 / pdf;
    return L_direct + L_indirect;
}