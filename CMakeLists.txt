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

add_executable(Renderer main.cpp Ray.h Material/Material.h Light/Light.h Object.h Math.h Math/Vector3.h Scene.h Renderer.h Camera/PerspectiveCamera.h Sphere.h Integrator/Integrator.h Film.h Shape/Shape.h Random.h Sampler/Sampler.h Math/Vector2.h Math/Matrix4.h Math/Vector4.h Camera/Camera.h Sampler/TrapezoidalSampler.h Intersection.h)
