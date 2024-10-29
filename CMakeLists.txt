cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cs200-assignment-4 VERSION 1)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(GLEW REQUIRED)

add_compile_options (-fdiagnostics-color=always)
add_compile_options(-Wextra -Wall -Wpedantic -std=c++11)

# Assignment 1
add_library(Affine Affine.cpp)
target_link_libraries(Affine PRIVATE glm::glm)

# Assignment 2 My Mesh
# add_library(MyMesh MyMesh.cpp)
# target_link_libraries(MyMesh PRIVATE glm::glm)

# Assignment 2 Square Mesh
add_library(SquareMesh SquareMesh.cpp)
target_link_libraries(SquareMesh PRIVATE glm::glm)

# Assignment 3
add_library(SolidRender SolidRender.cpp)
target_link_libraries(SolidRender PRIVATE glm::glm)

# Assignment 4
add_library(Camera Camera.cpp)
target_link_libraries(Camera PRIVATE glm::glm)

# Linking all to demo driver
add_executable(CameraTest CameraTest.cpp)
target_link_libraries(CameraTest PRIVATE Camera SquareMesh SolidRender Affine OpenGL glm::glm SDL2::SDL2 ${GLEW_LIBRARIES})
include_directories(CameraTest ${GLEW_INCLUDE_DIRS})

# Linking all to test driver
add_executable(InverseTest InverseTest.cpp)
target_link_libraries(InverseTest PRIVATE Camera SquareMesh SolidRender Affine OpenGL glm::glm SDL2::SDL2 ${GLEW_LIBRARIES})
include_directories(InverseTest ${GLEW_INCLUDE_DIRS})

# vim:shiftwidth=2:
