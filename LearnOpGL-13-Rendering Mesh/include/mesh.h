#ifndef MYAPP_MESH_H
#define MYAPP_MESH_H
#include <vector>

#include "data.h"
#include "shader.h"

class Mesh
{
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    // Function
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void Draw(Shader shader);
private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};


#endif