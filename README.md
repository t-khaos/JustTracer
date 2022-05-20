# 软光追渲染器

## TODO List

- Object 几何物体 √
    - Sphere 球体 √
    - Model 模型
        - Mesh 网格
        - Triangle 三角形
        - Vertex 顶点
        - Texture 纹理
- Ray 射线 √
- HitResult 相交结果 √
- Renderer 渲染器 √
  - OpenMP多线程加速 √
- Film 胶片 √
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


## Issue List

- 超大直径（1e5）球体有渲染瑕疵
- 间接光照阴影渲染瑕疵