#ifndef MYAPP_CUBE_H
#define MYAPP_CUBE_H
#include "object.h"

class Cube : public Object
{
    public :
    Cube(float initial_size, glm::vec3 initial_position, glm::vec3 initial_rotation)
    {
        Init(initial_size, initial_position, initial_rotation);
    }

    void Init(const float initial_size, const glm::vec3 &initial_position, const glm::vec3 &initial_rotation)
    {
        size = initial_size;
        position = initial_position;
        rotation = initial_rotation;
        vertices = {
    // BACK (-Z)
    {{-size, -size, -size}, { 0.0f,  0.0f, -1.0f}},
    {{ -size, size, -size}, { 0.0f,  0.0f, -1.0f}},
    {{size,  size, -size}, { 0.0f,  0.0f, -1.0f}},
    {{ size,  size, -size}, { 0.0f,  0.0f, -1.0f}},
    {{size,  -size, -size}, { 0.0f,  0.0f, -1.0f}},
    {{ -size, -size, -size}, { 0.0f,  0.0f, -1.0f}},

    // FRONT (+Z)
    {{-size, -size,  size}, { 0.0f,  0.0f,  1.0f}},
    {{ size, -size,  size}, { 0.0f,  0.0f,  1.0f}},
    {{ size,  size,  size}, { 0.0f,  0.0f,  1.0f}},
    {{ size,  size,  size}, { 0.0f,  0.0f,  1.0f}},
    {{-size,  size,  size}, { 0.0f,  0.0f,  1.0f}},
    {{-size, -size,  size}, { 0.0f,  0.0f,  1.0f}},

    // LEFT (-X)
    {{-size,  size,  size}, {-1.0f,  0.0f,  0.0f}},
    {{-size,  size, -size}, {-1.0f,  0.0f,  0.0f}},
    {{-size, -size, -size}, {-1.0f,  0.0f,  0.0f}},
    {{-size, -size, -size}, {-1.0f,  0.0f,  0.0f}},
    {{-size, -size,  size}, {-1.0f,  0.0f,  0.0f}},
    {{-size,  size,  size}, {-1.0f,  0.0f,  0.0f}},

    // RIGHT (+X)
    {{ size, size,  -size}, { 1.0f,  0.0f,  0.0f}},
    {{ size,  size, size}, { 1.0f,  0.0f,  0.0f}},
    {{ size, -size, size}, { 1.0f,  0.0f,  0.0f}},
    {{ size,  -size, size}, { 1.0f,  0.0f,  0.0f}},
    {{ size, -size,  -size}, { 1.0f,  0.0f,  0.0f}},
    {{ size,  size,  -size}, { 1.0f,  0.0f,  0.0f}},

    // BOTTOM (-Y)
    {{-size, -size, -size}, { 0.0f, -1.0f,  0.0f}},
    {{ size, -size, -size}, { 0.0f, -1.0f,  0.0f}},
    {{ size, -size,  size}, { 0.0f, -1.0f,  0.0f}},
    {{ size, -size,  size}, { 0.0f, -1.0f,  0.0f}},
    {{-size, -size,  size}, { 0.0f, -1.0f,  0.0f}},
    {{-size, -size, -size}, { 0.0f, -1.0f,  0.0f}},

    // TOP (+Y)
    {{-size,  size, -size}, { 0.0f,  1.0f,  0.0f}},
    {{-size,  size,  size}, { 0.0f,  1.0f,  0.0f}},
    {{ size,  size,  size}, { 0.0f,  1.0f,  0.0f}},
    {{ size,  size,  size}, { 0.0f,  1.0f,  0.0f}},
    {{ size,  size, -size}, { 0.0f,  1.0f,  0.0f}},
    {{-size,  size, -size}, { 0.0f,  1.0f,  0.0f}},
};

        SetupObject();
    }
};

#endif //MYAPP_CUBE_H