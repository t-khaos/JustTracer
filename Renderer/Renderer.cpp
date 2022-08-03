
#include "Renderer.h"

void Renderer::Render() const
{

    std::vector<Color> pixels(film->width * film->height);
    Color color(0.0);
    std::vector<float> distances(spp);
    bool isSameObject = true;
    size_t prevRayObjIndex = 0;
//#pragma omp parallel for schedule(dynamic, 1) private(color)
    for (int y = film->height - 1; y >= 0; --y)
    {
        std::cout << 100.0 * (film->height - 1 - y) / (film->height - 1) << "%" << std::endl;
        for (int x = 0; x < film->width; x++)
        {
            color = Color(0.0);

            //多线程计算每个像素的颜色
            for (int index = 0; index < spp; index++)
            {
                //根据采样分布计算投射的光线方向参数
                //auto position = Vector2(x,y); //用来测试1spp
                auto position = sampler->CastRayByDistribution(x, y);
                float s = position.x / static_cast<float>(film->width - 1);
                float t = position.y / static_cast<float>(film->height - 1);
                //投射光线并累计颜色
                Ray ray = camera->GetRay(s, t);
                color += integrator->Li(ray, scene);
                distances.push_back(ray.distance);

                //当所有光线击中的物体暂时为同一物体 && 当前光线不是第一根光线 && 当前光线命中了其他物体 时
                if (isSameObject && index != 0 && prevRayObjIndex != ray.objIndex)
                {
                    isSameObject = false;
                }
                prevRayObjIndex = ray.objIndex;//上一根光线击中的物体索引
            }
            std::sort(distances.begin(),
                      distances.end(),
                      [](auto& left, auto& right)
                      {
                          return left > right;
                      }
            );//按距离从大到小排序
            if (distances.front() - distances.back() > 10 || !isSameObject)
            {
                pixels[(film->height - y - 1) * film->width + x] = Color(0.0f);//描边
            }
            else
            {
                pixels[(film->height - y - 1) * film->width + x] = color * (1 / static_cast<float>(spp));//将颜色处理后写入像素
            }
            distances.clear();
            isSameObject = true;
        }
    }

    //冲洗胶卷
    film->Develop(pixels);
}

