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
        Renderer

        Application.cpp

        Accelerator/AABB.h
        Accelerator/AABB.cpp
        Accelerator/BVH.h Accelerator/BVH.cpp


        BxDF/IdealDiffuseBxDF.h BxDF/IdealDiffuseBxDF.cpp
        BxDF/IdealSpecularBxDF.h BxDF/IdealSpecularBxDF.cpp
        BxDF/MicrofacetSpecularBxDF.h BxDF/MicrofacetSpecularBxDF.cpp

        Math/Global.h
        Math/Vector.h
        Math/Matrix.h
        Math/Math.h
        Math/Random.h
        Math/Vector.h

        Common/BxDF.h
        Common/Ray.h
        Common/Material.h
        Common/Object.h
        Common/HitResult.h
        Common/Light.h

        Integrator/MonteCarloPathIntegrator.h Integrator/MonteCarloPathIntegrator.cpp

        Material/DiffuseMaterial.h Material/DiffuseMaterial.cpp
        Material/MirrorMaterial.h Material/MirrorMaterial.cpp
        Material/MicrofacetMaterial.cpp Material/MicrofacetMaterial.h

        Object/Rectangle.h Object/Rectangle.cpp
        Object/Sphere.h Object/Sphere.cpp
        Object/Triangle.h Object/Triangle.cpp
        Object/Model.cpp

        Renderer/Renderer.h Renderer/Renderer.cpp
        Renderer/Film.cpp Renderer/Film.h
        Renderer/Scene.cpp Renderer/Scene.h
        Renderer/Sampler.h Renderer/Sampler.cpp
        Renderer/Camera.h Renderer/Camera.cpp
        Renderer/Integrator.h
        Common/BxDFResult.h Common/LightResult.h)
