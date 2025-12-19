#ifndef MYAPP_ARCBALL_CAMERA_H
#define MYAPP_ARCBALL_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

class ArcballCam
{
public:
    glm::vec3 pendingMousePos;
    bool dragging = false;

    ArcballCam(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), currentOrientation(1, 0, 0, 0),
      startOrientation(1, 0, 0, 0){};

    void beginDrag(double x, double y)
    {
        dragging = true;
        startMouse = {x, y};
        startOrientation = currentOrientation;
    };
    void drag(double x, double y)
    {
        if (!dragging) return;
        currentMouse = {x, y};

        glm::vec3 va = screenToArcball(startMouse.x, startMouse.y);
        glm::vec3 vb = screenToArcball(currentMouse.x, currentMouse.y);

        float angle = acosf(std::min(1.0f, glm::dot(va, vb)));
        glm::vec3 axis = glm::cross(va, vb);

        if (glm::length(axis) < 1e-5f) return;

        glm::quat delta = glm::angleAxis(angle, glm::normalize(axis));
        currentOrientation = delta * startOrientation;
    };
    void endDrag()
    {
        dragging = false;
    };

    glm::vec3 screenToArcball(float x, float y) const
    {
        float nx = (2.0f * x - screenWidth) / screenWidth;
        float ny = (screenHeight - 2.0f * y) / screenHeight;

        float len2 = nx * nx + ny * ny;

        if (len2 <= 1.0f)
            return {nx, ny, sqrtf(1.0f - len2)};
        else
            return glm::normalize(glm::vec3(nx, ny, 0.0f));
    }

    glm::vec3 getArcballVector(double x, double y)
    {
        glm::vec3 P = glm::vec3(
            (x/screenWidth * 2) - 1.0,
            (y/screenHeight * 2) - 1.0,
            0
        );

        P.y = -P.y;

        float op_squared = P.x * P.x + P.y * P.y;

        if (op_squared < 1.0f)
        {
            P.z = sqrt(1.0 - op_squared);
        }
        // else
        // {
        //     P = glm::normalize(P);
        // }

        return P;
    }

    inline float getAngle(glm::vec3 va, glm::vec3 vb)
    {
        return acos(glm::min(1.0f, glm::dot(va, vb)));
    }

    inline glm::vec3 getAxis(glm::vec3 va, glm::vec3 vb)
    {
        return glm::cross(va,vb);
    }

    inline glm::quat getDeltaRotation(glm::vec3 va, glm::vec3 vb)
    {
        return glm::angleAxis(getAngle(va, vb), glm::normalize(getAxis(va, vb)));
    }

    inline glm::mat4 getRotationMatrix() const
    {
        return glm::mat4_cast(currentOrientation);
    }

    inline void replace()
    {
        startOrientation = currentOrientation;
    }

private:
    int screenWidth, screenHeight;

    glm::quat currentOrientation;
    glm::quat startOrientation;

    glm::vec2 startMouse;
    glm::vec2 currentMouse;
};

#endif //MYAPP_ARCBALL_CAMERA_H