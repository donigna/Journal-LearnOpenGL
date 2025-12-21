//
// Created by donigna on 12/16/25.
//

#ifndef MYAPP_DATA_H
#define MYAPP_DATA_H

#include <string>
#include <glm/glm.hpp>
#include "assimp/types.h"

// Struct
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    uint id;
    std::string type;
    aiString path; // Store the path of the texture to compare with other textures.fbm
};

#endif //MYAPP_DATA_H