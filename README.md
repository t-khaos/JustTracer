# Just Tracer 软光追渲染器

## About & References

该项目是我个人在学习图形学过程中的练习项目，起源于跟着 Ray Tracing in One Weekend 系列第一部实现了简单的软光追渲染器，而后又阅读了其他各种软渲染器的代码，诸如 TinyRenderer, Nori, GAMES101作业7框架,
smallpt 以及各种魔改版, Pursuit, Filament PBR 文档等等，加上复现论文算法的需要，开始制作自己的软光追渲染器。

> 1. [Ray Tracing in One Weekend Series](https://raytracing.github.io/)
> 2. [smallpt - 99 行 C++ 代码实现全局光照](http://www.kevinbeason.com/smallpt/)
> 3. [vinjn 大佬提供的 smallpt 魔改版合集](https://github.com/vinjn/learn-raytracing)
> 4. [smallpt 改写为 pbrt - infancy 的中文教程](https://infancy.github.io/smallpt2pbrt.html)
> 5. [Pursuit - ksgfk 的软光追渲染器](https://github.com/ksgfk/Pursuit)
> 6. [Nori - Pursuit 作者的 Nori 作业解析](https://www.zhihu.com/column/c_1407025850030698496)
> 7. [TinyRenderer - 中文教程&修改版](https://zhuanlan.zhihu.com/p/399056546)
> 8. [Filament PBR 文档 - 中文翻译](https://jerkwin.github.io/filamentcn/Filament.md.html)
> 9. [GAME101 - liupeining 的作业 7 实现](https://github.com/liupeining/Games_101_homework/tree/main/a7)
> 10. [RenderHelp - 矢量模板写的特别好的软光栅化渲染器](https://github.com/skywind3000/RenderHelp)
> 11. [Mitsuba1/2 科研用的渲染器可以看看源代码](http://www.mitsuba-renderer.org/) 
> 12. [pbrt - 众所周知的圣经](https://www.pbr-book.org/3ed-2018/contents)


## TODO

- PBR 材质
- 空间加速结构
- 模型加载和解析
- 透视相机
- 点光源
- Cornell Box 场景
- 场景 Json 文件解析
- 纹理贴图

## Features

- Object 物体 √
    - Sphere 球体 √
    - Model 模型
        - Mesh 网格
        - Triangle 三角形 √
        - Texture 纹理
- Ray 射线 √
- HitResult 相交结果 √
- Renderer 渲染器 √
  - OpenMP多线程加速 √
- Film 胶片 √
  - 输出PPM格式图片 √
  - 使用第三方库输出常用格式图片
- Scene 场景 √
- Camera 相机 √
  - PerspectiveCamera 透视相机 √
  - OrthogonalCamera 正交相机
- Sampler 采样器 √
  - TrapezoidalSampler 梯形分布采样器 √
- Integrator 积分器 √
  - MonteCarloPathIntegrator 蒙特卡洛路径追踪积分器 √
    - 对光源采样 √
  - SimplePathIntegrator 简单路径追踪积分器 √
  - NormalIntegrator 法线可视化积分器 √
- Material 材质 √
  - DiffuseMaterial 漫反射材质 √
  - ReflectMaterial 镜面反射材质 √
  - RefractMaterial 折射材质
  - MircofacetMaterial 微表面材质
- Light 灯光 √
  - SphereLight 体积光源 - 球体 √
  - AreaLight 面光源 √
- Accelerator 加速结构
  - AABB 轴向包围盒
  - BVH 层次包围体
  - KD-Tree 二叉树
- Tool 工具 
  - Vector 向量 √
  - Matrix 矩阵 √
  - Global 全局 √
    - 随机数生成器 √
  - ObjLoader 模型obj文件解析 
  - JsonLoader 场景json文件解析
  - TextureLoader 纹理文件解析


## Dependencies

以后可能会加上 stb_image 头文件以支持输出其他格式图片

## Issues

- 超大直径（1e5）球体有渲染瑕疵
- 相机透视变形