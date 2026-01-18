#include <iostream>
#include <cmath>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <vector>
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
void frame_buffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void do_movement();
unsigned int loadTexture(const char *path);

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

    // stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    Shader shader("C:/Users/donin/Projects/Journal-LearnOpenGL-master/LearnOpGL-15-Advance-Blending/assets/shaders/blending.vert", "C:/Users/donin/Projects/Journal-LearnOpenGL-master/LearnOpGL-15-Advance-Blending/assets/shaders/blending.frag");

    float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
        5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
        1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f};

    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    // Load texture
    unsigned int transparentTexture = loadTexture("C:/Users/donin/Projects/Journal-LearnOpenGL-master/LearnOpGL-15-Advance-Blending/assets/textures/grass.png");
    unsigned int floorTexture = loadTexture("C:/Users/donin/Projects/Journal-LearnOpenGL-master/LearnOpGL-15-Advance-Blending/assets/textures/container2.png");

    // transparent vegetation locations
    // --------------------------------
    std::vector<glm::vec3> vegetation{
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3(1.5f, 0.0f, 0.51f),
        glm::vec3(0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3(0.5f, 0.0f, -0.6f)};

    shader.Use();
    shader.SetInt("texture1", 0);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shader.Use();

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
        shader.SetMat4("model", model);
        shader.SetMat4("projection", projection);
        shader.SetMat4("view", view);
        // ourShader.SetVec3("lightPos", lightPos);
        // ourShader.SetVec3("lightColor", glm::vec3(1.0f,1.0f, 1.0f));

        // floor
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        model = glm::mat4(1.0f);
        shader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // vegetation
        glBindVertexArray(transparentVAO);
        glBindTexture(GL_TEXTURE_2D, transparentTexture);
        for (unsigned int i = 0; i < vegetation.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, vegetation[i]);
            shader.SetMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (action == GLFW_PRESS)
        {
            arcballCam.beginDrag(x, y);
        }
        else if (action == GLFW_RELEASE)
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

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    arcballCam.drag(xpos, ypos);
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

void frame_buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
