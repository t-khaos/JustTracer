cmake_minimum_required(VERSION 3.22)
project(JustTracer)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(Renderer main.cpp Ray.hpp Material.hpp Light.hpp Object.hpp Math.hpp Vector.hpp Scene.hpp Renderer.hpp Camera.hpp Sphere.hpp)

# openMP 配置
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()