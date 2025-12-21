#include <iostream>
#include <cmath>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Other includes
#include "shader.h"
#include "assets.h"
#include "camera.h"
#include "arcball_camera.h"
#include "model.h"
#include "object/cube.h"

// Function prototypes
void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void do_movement();

// Window dimensions
const unsigned int WIDTH = 1080, HEIGHT = 720;

// Camera
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

// Arcball Camera
ArcballCam arcballCam(WIDTH, HEIGHT);
float fov = 45;
float maxFov = 90;
float Front = 10;

glm::vec2 mouseStartPos;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f; // Time between current frame and last frame
GLfloat lastFrame = 0.0f; // Time of last frame

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // GLFW Options
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAS" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    // glDepthMask(GL_FALSE); // disable writing the depth buffer
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);

    Shader ourShader("../assets/shaders/1_model_loading.vert", "../assets/shaders/1_model_loading.frag");
    glEnable(GL_CULL_FACE);
    Model ourModel("../assets/models/backpack/backpack.obj");

    Shader outlineShader("../assets/shaders/outline_shader.vert","../assets/shaders/outline_shader.frag");

    // Shader cubeShader("../assets/shaders/object_shader.vert", "../assets/shaders/object_shader.frag");
    // Cube cube(0.5f, glm::vec3(0.5f), glm::vec3(1));

    // orbit variable
    float orbitRadius = 3.0f;
    float orbitAngularSpeed = 1.0f;
    float orbitAngle = 0.0f;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        glStencilMask(0x00);
        ourShader.Use();

        // float currentFrame = glfwGetTime();
        // static float lastFrame = currentFrame;
        // float deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;
        // orbitAngle += orbitAngularSpeed * deltaTime;
        // glm::vec3 lightPos = glm::vec3(orbitRadius * cos(orbitAngle), 0, orbitRadius * sin(orbitAngle));

        glm::mat4 model = arcballCam.getRotationMatrix();
        glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, Front),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(
            glm::radians(35.0f),
            (float)WIDTH / (float)HEIGHT,
            0.1f,
            1000.0f);

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.SetMat4("model", model);
        ourShader.SetMat4("projection", projection);
        ourShader.SetMat4("view", view);
        // ourShader.SetVec3("lightPos", lightPos);
        // ourShader.SetVec3("lightColor", glm::vec3(1.0f,1.0f, 1.0f));

        // Stencil settings
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1,  0xFF);
        glStencilMask(0xFF);
        // render the loaded model
        ourModel.Draw(ourShader);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        outlineShader.Use();
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.0f));
        outlineShader.SetMat4("model", model);
        outlineShader.SetMat4("projection", projection);
        outlineShader.SetMat4("view", view);
        ourModel.Draw(outlineShader);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (action == GLFW_PRESS)
        {
            arcballCam.beginDrag(x,y);
        } else if (action == GLFW_RELEASE)
        {
            arcballCam.endDrag();
        }
    }
}


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    arcballCam.drag(xpos,ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(yoffset);
    Front -= (float)yoffset;
    if (Front < 1.0f)
        Front = 1.0f;
    else if (Front >= 1000)
        Front = 100;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
