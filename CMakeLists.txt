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

        Accelerator/BVH.h
        Accelerator/KDTree.h
        Accelerator/AABB.h

        Camera/PerspectiveCamera.h Camera/PerspectiveCamera.cpp

        Common/Ray.h
        Common/Global.h
        Common/Vector.h
        Common/Matrix.h
        Common/Camera.h
        Common/Vector.h
        Common/Material.h
        Common/Object.h
        Common/HitResult.h
        Common/Sampler.h
        Common/Integrator.h
        Common/Light.h

        Integrator/PathIntegrator.h
        Integrator/NormalIntegrator.h Integrator/NormalIntegrator.cpp
        Integrator/SimplePathIntegrator.h Integrator/SimplePathIntegrator.cpp
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

        Sampler/TrapezoidalSampler.h Sampler/TrapezoidalSampler.cpp
)
