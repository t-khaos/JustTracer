
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

    //击中光源直接返回光源自发光
    if (hitResult.material->type == MaterialType::Light)
        return hitResult.material->emission;

    //直接光照
    //--------------------------------------------------------------------
    Vector3 L_direct;

    //击中物体则对光源均匀采样
    LightResult lightResult;
    scene->SampleLight(lightResult);

    //计算交点到光源方向和距离
    Vector3 toLightDir = lightResult.point - hitResult.point;
    Vector3 toLightDirN = Normalize(toLightDir);
    float distance = Length(toLightDir);

    //采样BxDF
    BxDFResult bxdf = hitResult.material->SampleBxDF(toLightDirN, -ray.direction, hitResult.normal);

    //向交点到光源方向投射光线
    Ray shadowRay(hitResult.point, toLightDirN);
    //计算光线与场景求交
    HitResult shadowResult;
    scene->Intersect(shadowRay, shadowResult);
    //遮挡&&镜面反射无直接光照
    if (shadowResult.distance - distance > -EPSILON && (!bxdf.isDelta)) {
        L_direct = lightResult.emission * bxdf.fr
                   * Dot(toLightDirN, hitResult.normal)
                   * Dot(-toLightDirN, lightResult.normal)
                   / (distance * distance) / lightResult.pdf;
    }

    //间接光照
    //--------------------------------------------------------------------
    Vector3 L_indirect;

    //至少3次递归再进行轮盘赌
    if (depth >= 3 && RandomFloat() >= P_RR)
        return L_direct;

    //生成光线，向该方向投射
    Ray nextRay(hitResult.point, bxdf.direction);
    HitResult nextResult;
    //未击中物体则无间接光照
    if (!scene->Intersect(nextRay, nextResult))
        return L_direct;

    //镜面反射击中光源特殊处理
    if(!nextResult.isLight){
        L_indirect = bxdf.fr * Dot(bxdf.direction, hitResult.normal) / bxdf.pdf / P_RR
                     * CastRay(nextRay, scene, ++depth);
    }else if(bxdf.isDelta){
        L_indirect = bxdf.fr * Dot(bxdf.direction, hitResult.normal) / bxdf.pdf / P_RR;
    }

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
