#ifndef MYAPP_OBJECT_H
#define MYAPP_OBJECT_H
#include "shader.h"
#include "data.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Object
{
protected:
    unsigned int VAO, VBO, EBO;
    float size;
    std::vector<Vertex> vertices;

public:
    glm::vec3 position;
    glm::vec3 rotation;

    void SetupObject()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        // Bind vertex arrays and buffer
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(float), &this->indices[0], GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // Normal positions
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // TODO: Vertex normals

        // TODO: Vertex texcoords


        // Clear bindings
        glBindVertexArray(0);
    }

    void Draw(const Shader &shader) const
    {
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);
    }

    virtual void Move()
    {
        // TODO: change object position
    };

    virtual void Rotate()
    {
        // TODO: change object rotation
    };
};

#endif //MYAPP_OBJECT_H