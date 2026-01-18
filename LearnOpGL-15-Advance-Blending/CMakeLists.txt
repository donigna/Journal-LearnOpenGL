cmake_minimum_required(VERSION 3.21)

# Set Toolchain to use VCPKG 
# Make sure you have VCPKG_ROOT in environment variable
## Or if you already run vcpkg integrate install, this code won't effect anything
set(CMAKE_TOOLCHAIN_FILE
    "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
    
project(MyEngine LANGUAGES C CXX)
    
set(CMAKE_CXX_STANDARD 17)


cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
#find_package(soil CONFIG REQUIRED)

file(GLOB APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

add_executable(my_engine
    ${APP_SOURCES}
)

target_include_directories(my_engine PRIVATE
    external
    include
)

target_link_libraries(my_engine PRIVATE
    OpenGL::GL
    glfw
    glm::glm
    assimp::assimp
    glad::glad
)

target_compile_definitions(my_engine PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

if (UNIX AND NOT APPLE)
    target_link_libraries(my_engine PRIVATE m dl)
endif()
