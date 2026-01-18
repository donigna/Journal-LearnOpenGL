cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Path to GLFW by manual installation
include_directories($ENV{CMAKE_ROOT}/usr/include)
link_directories($ENV{CMAKE_ROOT}/usr/lib)

# Add include path to GLAD
include_directories(${CMAKE_SOURCE_DIR}/external)
# Add internal include path
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(my_app 
    src/main.cpp
)
target_link_libraries(my_app PRIVATE OpenGL::GL  GLEW::GLEW glfw SOIL m dl)
