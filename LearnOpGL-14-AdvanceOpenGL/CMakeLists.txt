cmake_minimum_required(VERSION 3.21)
project(MyApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
#find_package(soil CONFIG REQUIRED)

file(GLOB APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

add_executable(my_app
    ${APP_SOURCES}
)

target_include_directories(my_app PRIVATE
    external
    include
)

target_link_libraries(my_app PRIVATE
    OpenGL::GL
    glfw
    glm::glm
    assimp::assimp
    glad::glad
)

target_compile_definitions(my_app PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

if (UNIX AND NOT APPLE)
    target_link_libraries(my_app PRIVATE m dl)
endif()
