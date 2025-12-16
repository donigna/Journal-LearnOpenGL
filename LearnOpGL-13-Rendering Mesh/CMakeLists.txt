cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

# Path to GLFW by manual installation
include_directories($ENV{CMAKE_ROOT}/usr/include)
link_directories($ENV{CMAKE_ROOT}/usr/lib)

add_executable(my_app 
src/main.cpp
external/glad/glad.c
        src/mesh.cpp
        include/mesh.h
        include/data.h
)

# Include dirrectories
target_include_directories(my_app PRIVATE 
    external
    include
)

# Link libraries
target_link_libraries(my_app PRIVATE 
    OpenGL::GL 
    glfw 
    m 
    dl
)

