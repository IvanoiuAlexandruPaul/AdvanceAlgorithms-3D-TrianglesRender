cmake_minimum_required(VERSION 3.17)
project(New_folder__2_)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp Clipping.cpp Clipping.h
        Fragment.cpp Fragment.h
        Matrix.cpp Matrix.h
        ModelTransform.cpp ModelTransform.h
        Pipeline.cpp Pipeline.h
        Projection.cpp Projection.h
        ScreenMapping.cpp ScreenMapping.h
        Triangle.cpp Triangle.h
        Vertex.cpp Vertex.h)
file(GLOB SOURCES
        header-folder/*.h
        source-folder/*.cpp
        )
add_executable(New_folder__2_ main.cpp Clipping.cpp Clipping.h
        Fragment.cpp Fragment.h
        Matrix.cpp Matrix.h
        ModelTransform.cpp ModelTransform.h
        Pipeline.cpp Pipeline.h
        Projection.cpp Projection.h
        ScreenMapping.cpp ScreenMapping.h
        Triangle.cpp Triangle.h
        Vertex.cpp Vertex.h)