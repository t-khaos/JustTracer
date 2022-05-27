
#include "MonteCarloPathIntegrator.h"
#include "../Math/Random.h"
#include "../Math/Math.h"

Color3d MonteCarloPathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}

Color3d MonteCarloPathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    //递归超过指定层数结束
    if (depth >= depth_max)
        return Color3d(0.0);

    //光线与场景求交
    //--------------------------------------------------------------------
    HitResult result;
    if (!scene->Intersect(ray, result))
        return Color3d(0.0);
    //颜色重映射
    //第一次击中物体,获取物体表面信息
    if (depth == 0)
        firstHitResult = HitResult(result);

    //击中光源
    //--------------------------------------------------------------------
    //直接返回光源自发光
    if (result.material->type == MaterialType::LIGHT)
        return result.material->emission;

    //击中物体
    //--------------------------------------------------------------------
    Vector3d L_direct, L_indirect;

    /* ==================================================================== */
    /*                     Direct illumination sampling                     */
    /* ==================================================================== */

    //获取采样pdf，在光源表面均选取采样的位置
    HitResult sampleLightResult;
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
        if (result.material->type == MaterialType::REFLECT) {

        } else {
            L_direct = sampleLightResult.material->emission
                       * result.material->EvalColor(ray.direction, toLightDirN, result.normal)
                       * Dot(toLightDirN, result.normal)
                       * Dot(-toLightDirN, sampleLightResult.normal)
                       / (distance * distance)
                       / scene->lights[0]->PDF();
        }
    }

    /* ==================================================================== */
    /*                     Indirect illumination sampling                     */
    /* ==================================================================== */
    //随机采样反射方向
    Vector3d nextDir = result.material->SampleDirection(ray.direction, result.normal);
    Vector3d nextDirN = Normalize(nextDir);

    //至少3次递归再进行轮盘赌 && 角度合适
    if ((depth < 3 || RandomDouble() < P_RR) && Dot(nextDirN, result.normal) > 0.0) {
        //生成光线，向该方向投射
        Ray nextRay(result.point, nextDirN);
        HitResult nextResult;
        //必须击中物体 && 击中的物体不能是为光源
        if (scene->Intersect(nextRay, nextResult)) {
            if (nextResult.material->type != MaterialType::LIGHT) {
                //击中物体则继续递归
                L_indirect = CastRay(nextRay, scene, ++depth)
                             * result.material->EvalColor(ray.direction, nextDirN, result.normal)
                             * Dot(nextDirN, result.normal)
                             / result.material->PDF(ray.direction, nextDirN, result.normal)
                             / P_RR;
            } else {
                if (result.material->type == MaterialType::REFLECT) {
                    L_indirect = Color3d(1.0);
                }
            }
        }
    }

    Color3d color = L_direct + L_indirect;
    //颜色重映射
/*    if (firstHitResult.material &&
        firstHitResult.material->type == MaterialType::DIFFUSE_IDEAL_REMAP) {
        RemapColor(color);
    }*/
    return color;
}