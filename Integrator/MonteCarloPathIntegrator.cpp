
#include "MonteCarloPathIntegrator.h"

Color MonteCarloPathIntegrator::Li(const Ray &ray, std::shared_ptr<Scene> scene) {
    return CastRay(ray, scene, 0);
}

Color MonteCarloPathIntegrator::CastRay(const Ray &ray, std::shared_ptr<Scene> scene, int depth) {
    //递归超过指定层数结束
    if (depth >= depth_max)
        return Color(0.0f);

    //光线与场景求交
    //--------------------------------------------------------------------
    HitResult hitResult;
    if (!scene->Intersect(ray, hitResult))
        return Color(0.0f);

    //击中光源
    //--------------------------------------------------------------------
    //直接返回光源自发光
    if (hitResult.material->type == MaterialType::Light)
        return hitResult.material->emission;

    Vector3 L_direct, L_indirect;

    //对光源均匀采样
    LightResult lightSampleResult;
    scene->SampleLight(lightSampleResult);

    //计算交点到光源方向和距离
    Vector3 toLightDir = lightSampleResult.point - hitResult.point;
    Vector3 toLightDirN = Normalize(toLightDir);
    float distance = Length(toLightDir);

    //采样BxDF
    BxDFResult bxdf = hitResult.material->SampleBxDF(toLightDirN, -ray.direction, hitResult.normal);

    /* ==================================================================== */
    /*                     Direct illumination sampling                     */
    /* ==================================================================== */
    //向交点到光源方向投射光线
    Ray toLightRay(hitResult.point, toLightDirN);
    //计算光线与场景求交
    HitResult lightHitResult;
    scene->Intersect(toLightRay, lightHitResult);
    //遮挡&&镜面反射无直接光照
    if (lightHitResult.distance - distance > -EPSILON && (!bxdf.isDelta)) {
        L_direct = lightSampleResult.emission * bxdf.fr
                   * Dot(toLightDirN, hitResult.normal)
                   * Dot(-toLightDirN, lightSampleResult.normal)
                   / (distance * distance) / lightSampleResult.pdf;
    }

    /* ==================================================================== */
    /*                     Indirect illumination sampling                     */
    /* ==================================================================== */
    //至少3次递归再进行轮盘赌
    if (depth >= 3 && RandomFloat() >= P_RR)
        return L_direct;

    //生成光线，向该方向投射
    Ray nextRay(hitResult.point, bxdf.direction);
    HitResult nextResult;

    //必须击中物体
    if (!scene->Intersect(nextRay, nextResult))
        return L_direct;

    //镜面反射击中光源特殊处理
    L_indirect = bxdf.fr * Dot(bxdf.direction, hitResult.normal) / bxdf.pdf / P_RR
                 * (nextResult.isLight ? (float) bxdf.isDelta : CastRay(nextRay, scene, ++depth));

    return L_direct + L_indirect;
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
