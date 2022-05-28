
#include "MonteCarloPathIntegrator.h"
#include "../Math/Random.h"
#include "../Math/Math.h"
#include "../Common/BxDF.h"

Color MonteCarloPathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}

Color MonteCarloPathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    //递归超过指定层数结束
    if (depth >= depth_max)
        return Color(0.0);

    //光线与场景求交
    //--------------------------------------------------------------------
    HitResult result;
    if (!scene->Intersect(ray, result))
        return Color(0.0);
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
    Vector3 L_direct, L_indirect;

    /* ==================================================================== */
    /*                     Direct illumination sampling                     */
    /* ==================================================================== */

    //获取采样pdf，在光源表面均选取采样的位置
    HitResult sampleLightResult;
    scene->lights[0]->SampleHitResult(sampleLightResult);
    //交点与采样点方向
    Vector3 toLightDir = sampleLightResult.point - result.point;
    Vector3 toLightDirN = Normalize(toLightDir);
    float distance = Length(toLightDir);
    //生成光线，向该方向投射，获取与光源交点的信息
    Ray toLightRay(result.point, toLightDirN);
    HitResult toLightResult;
    scene->Intersect(toLightRay, toLightResult);
    //采样BxDF
    BxDFResult bxdf = result.material->SampleBxDF(toLightDirN, -ray.direction, result.normal);
    float pdf_light = scene->lights[0]->PDF();

    //阴影测试
    if (toLightResult.distance - distance > -EPSILON) {
        //镜面反射不计算直接光
        if (!bxdf.isDelta)
            L_direct = sampleLightResult.material->emission
                       * bxdf.fr
                       * Dot(toLightDirN, result.normal)
                       * Dot(-toLightDirN, sampleLightResult.normal)
                       / (distance * distance)
                       / pdf_light;
    }

    /* ==================================================================== */
    /*                     Indirect illumination sampling                     */
    /* ==================================================================== */
    //至少3次递归再进行轮盘赌
    if (depth >= 3 && RandomFloat() >= P_RR)
        return L_direct;

    //角度
    if (Dot(bxdf.direction, result.normal) < 0.0)
        return L_direct;

    //生成光线，向该方向投射
    Ray nextRay(result.point, bxdf.direction);
    HitResult nextResult;

    //必须击中物体
    if (!scene->Intersect(nextRay, nextResult))
        return L_direct;

    //镜面反射击中光源特殊处理
    if (nextResult.material->type == MaterialType::LIGHT){
        if(bxdf.isDelta)
            L_direct = bxdf.fr
                       * Dot(bxdf.direction, result.normal)
                       / bxdf.pdf
                       / P_RR;
    }
    else{
        L_indirect = CastRay(nextRay, scene, ++depth)
                     * bxdf.fr
                     * Dot(bxdf.direction, result.normal)
                     / bxdf.pdf
                     / P_RR;
    }
    Color color = L_direct + L_indirect;
    //颜色重映射
/*    if (firstHitResult.material &&
        firstHitResult.material->type == MaterialType::DIFFUSE_IDEAL_REMAP) {
        RemapColor(color);
    }*/
    return color;
}