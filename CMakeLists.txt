cmake_minimum_required(VERSION 3.22)
project(JustTracer)


# openMP 配置
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(
    Renderer main.cpp Ray.h Light/Light.h Intersection.h
    Tool/Global.h Tool/Vector3.h Tool/Vector2.h Tool/Matrix4.h Tool/Vector4.h
    Material/Material.h Material/MicrofacetMaterial.h
    Scene.h Renderer.h Film.h
    Camera/Camera.h Camera/PerspectiveCamera.h
    Object.h Sphere.h Shape/Shape.h
    Sampler/Sampler.h Sampler/TrapezoidalSampler.h
    Integrator/Integrator.h Integrator/NormalIntegrator.h
        Shape/Triangle.h Shape/Mesh.h Shape/Model.h Shape/Vertex.h Shape/Texture.h Accelerator/BVH.h Accelerator/KDTree.h Accelerator/AABB.h Integrator/SimplePathIntegrator.h Material/DiffuseMaterial.h Material/RefractMaterial.h Integrator/MonteCarloPathIntegrator.h Integrator/PathIntegrator.h)
