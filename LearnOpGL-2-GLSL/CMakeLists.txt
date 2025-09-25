cmake_minimum_required(VERSION 3.10)
project(LearnO)

set(CMAKE_CXX_STANDARD 17)

# Path to GLFW by manual installation
include_directories($ENV{HOME}/local/include)
link_directories($ENV{HOME}/local/lib)

# Add include path to GLAD
include_directories(${CMAKE_SOURCE_DIR}/glad/include)
include_directories(src/)

add_executable(my_app 
    src/main.cpp
    glad/src/glad.c  
)
target_link_libraries(my_app PRIVATE glfw)
