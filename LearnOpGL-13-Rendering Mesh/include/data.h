//
// Created by donigna on 12/16/25.
//

#ifndef MYAPP_DATA_H
#define MYAPP_DATA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>

// Struct
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    std::string type;
};

#endif //MYAPP_DATA_H