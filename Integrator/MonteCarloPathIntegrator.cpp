
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
        return Color(0.0f);

    //光线与场景求交
    //--------------------------------------------------------------------
    HitResult result;
    if (!scene->Intersect(ray, result))
        return Color(0.0f);

    //击中光源
    //--------------------------------------------------------------------
    //直接返回光源自发光
    if (result.material->type == MaterialType::Light)
        return result.material->emission;

    Vector3 L_direct, L_indirect;

    //对光源均匀采样
    HitResult sampleLightResult;
    scene->lights[0]->SampleHitResult(sampleLightResult);
    //获取光源采样的概率密度函数
    float pdf_light = scene->lights[0]->PDF();

    //计算交点到光源方向
    Vector3 toLightDir = sampleLightResult.point - result.point;
    Vector3 toLightDirN = Normalize(toLightDir);
    //计算交点到光源距离
    float distance = Length(toLightDir);

    //采样BxDF
    BxDFResult bxdf = result.material->SampleBxDF(toLightDirN, -ray.direction, result.normal);


    /* ==================================================================== */
    /*                     Direct illumination sampling                     */
    /* ==================================================================== */
    //向交点到光源方向投射光线
    Ray toLightRay(result.point, toLightDirN);
    //计算光线与场景求交
    HitResult toLightResult;
    scene->Intersect(toLightRay, toLightResult);

    //比较距离 && 镜面反射不计算直接光
    L_direct = sampleLightResult.material->emission
               * bxdf.fr / (distance * distance) / pdf_light
               * Dot(toLightDirN, result.normal) * Dot(-toLightDirN, sampleLightResult.normal)
               * (float)((!bxdf.isDelta)&&(toLightResult.distance - distance > -EPSILON));


    /* ==================================================================== */
    /*                     Indirect illumination sampling                     */
    /* ==================================================================== */
    //至少3次递归再进行轮盘赌
    if (depth >= 3 && RandomFloat() >= P_RR)
        return L_direct;

    //生成光线，向该方向投射
    Ray nextRay(result.point, bxdf.direction);
    HitResult nextResult;

    //必须击中物体
    if (!scene->Intersect(nextRay, nextResult))
        return L_direct;

    //镜面反射击中光源特殊处理
    L_indirect = bxdf.fr * Dot(bxdf.direction, result.normal) / bxdf.pdf / P_RR
                 * (nextResult.isLight ? (float) bxdf.isDelta : CastRay(nextRay, scene, ++depth));

    return  L_direct + L_indirect;
}


//颜色重映射
/*    //第一次击中物体,获取物体表面信息
    if (depth == 0)
        firstHitResult = HitResult(result);*/

//颜色重映射
/*    if (firstHitResult.material &&
        firstHitResult.material->type == MaterialType::Remap) {
        RemapColor(color);
    }*/
