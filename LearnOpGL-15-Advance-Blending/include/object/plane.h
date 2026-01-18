#ifndef MYAPP_CUBE_H
#define MYAPP_CUBE_H
#include "object.h"

class Plane : public Object
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
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
};

        SetupObject();
    }
};

#endif //MYAPP_CUBE_H