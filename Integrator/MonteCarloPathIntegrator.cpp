
#include "MonteCarloPathIntegrator.h"
#include "../Math/Random.h"

Color3d MonteCarloPathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}

Color3d MonteCarloPathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    //递归超过指定层数结束
    if (depth >= depth_max)
        return Color3d(0.0);
    //光线与场景求交
    HitResult result;
    if (!scene->Intersect(ray, result))
        return Color3d(0.0);
    //击中光源
    if (result.material->type == MaterialType::LIGHT)
        return result.material->emission;
    //击中物体
    Vector3d L_direct, L_indirect;
    HitResult sampleLightResult;
    //1.对光源采样，获取采样pdf，在光源表面均选取采样的位置
    double pdf_light = scene->lights[0]->PDF();
    scene->lights[0]->SampleHitResult(sampleLightResult);
    //交点与采样点方向
    Vector3d toLightDir = sampleLightResult.point - result.point;
    Vector3d toLightDirN = Normalize(toLightDir);
    double distance = Length(toLightDir);
    //生成光线，向该方向投射，获取与光源交点的信息
    Ray toLightRay(result.point, toLightDirN);
    HitResult toLightResult;
    scene->Intersect(toLightRay, toLightResult);

    if (toLightResult.distance - distance > -EPSILON) {
        //L_dir = L_i * EvalColor * cos_theta * cos_theta_x / | x - p | ^ 2 / pdf_light
        L_direct = sampleLightResult.material->emission //光源自发光项
                   * result.material->EvalColor(ray.direction, toLightDirN, result.normal)
                   * Dot(toLightDirN, result.normal) //光线方向与物体交点的夹角余弦
                   * Dot(-toLightDirN, sampleLightResult.normal)//-光线方向与光源交点的夹角余弦
                   / (distance * distance)//光照强度随距离的平方减弱
                   / pdf_light;
    }
    //建议至少3次递归再进行轮盘赌
    if (depth > 3 && RandomDouble() > P_RR)
        return L_direct;
    //2.对交点采样，随机采样反射方向
    Vector3d nextDir = result.material->SampleDirection(ray.direction, result.normal);
    Vector3d nextDirN = Normalize(nextDir);
    //生成光线，向该方向投射
    Ray nextRay(result.point, nextDirN);
    HitResult nextResult;
    //是否击中物体
    if (!scene->Intersect(nextRay, nextResult))
        return L_direct;
    //击中的物体是否为光源
    if (nextResult.material->type == MaterialType::LIGHT)
        return L_direct;
    //击中物体则继续递归
    //获取交点材质的pdf
    double pdf = result.material->PDF(ray.direction, nextDirN, result.normal);
    // CastRay() * EvalColor() * cos_theta / P_RR / pdf;


    L_indirect = CastRay(nextRay, scene, ++depth)
                 * result.material->EvalColor(ray.direction, nextDirN, result.normal)
                 * Dot(nextDirN, result.normal)
                 / pdf
                 / P_RR;
    return L_direct + L_indirect;
}