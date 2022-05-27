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

        Renderer/Camera.cpp

        Accelerator/AABB.h
        Common/Ray.h
        Math/Global.h
        Math/Vector.h
        Math/Matrix.h
        Renderer/Camera.h
        Math/Vector.h
        Common/Material.h
        Common/Object.h
        Common/HitResult.h
        Renderer/Sampler.h
        Renderer/Integrator.h
        Common/Light.h
        Accelerator/BVH.h

        Integrator/MonteCarloPathIntegrator.h Integrator/MonteCarloPathIntegrator.cpp

        Material/DiffuseMaterial.h Material/DiffuseMaterial.cpp
        Material/ReflectMaterial.h Material/ReflectMaterial.cpp
        Material/MicrofacetMaterial.cpp

        Object/Rectangle.h Object/Rectangle.cpp
        Object/Sphere.h Object/Sphere.cpp
        Object/Triangle.h Object/Triangle.cpp
        Object/Model.cpp


        Renderer/Renderer.h Renderer/Renderer.cpp
        Renderer/Film.cpp Renderer/Film.h
        Renderer/Scene.cpp Renderer/Scene.h

        Renderer/Sampler.h Renderer/Sampler.cpp
        Math/Math.h Math/Random.h Accelerator/AABB.cpp Accelerator/BVH.cpp Test/CornellBox.h Test/Remap.h)
