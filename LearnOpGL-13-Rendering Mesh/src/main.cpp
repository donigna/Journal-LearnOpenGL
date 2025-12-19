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
const unsigned int WIDTH = 1920, HEIGHT = 1080;

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

// The MAIN function, from here we start the application and run the game loop
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

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f),
    };

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    // Shader lampShader(Assets::light_source_vert.c_str(), Assets::light_source_frag.c_str());
    Shader ourShader("../assets/shaders/1_model_loading.vert", "../assets/shaders/1_model_loading.frag");
    glEnable(GL_CULL_FACE);
    Model ourModel("../assets/models/backpack/backpack.obj");

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // float currentFrame = static_cast<float>(glfwGetTime());
        // deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // don't forget to enable shader before setting uniforms
        ourShader.Use();

        glm::mat4 model = arcballCam.getRotationMatrix();
        glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, Front),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(
            glm::radians(35.0f),
            (float)WIDTH / (float)HEIGHT,
            0.1f,
            100.0f);

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
        // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.SetMat4("model", model);
        ourShader.SetMat4("projection", projection);
        ourShader.SetMat4("view", view);


        // view projection arcball cam

        // glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // view projection cam
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
        // glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        // glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // glm::mat4 view = camera.GetViewMatrix();

        // render the loaded model
        ourModel.Draw(ourShader);


        // Swap the screen buffers
        glfwSwapBuffers(window);
        // glfwPollEvents();
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Activate this if you using First person camera
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
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
    // if (key >= 0 && key < 1024)
    // {
    //     if (action == GLFW_PRESS)
    //         keys[key] = true;
    //     else if (action == GLFW_RELEASE)
    //         keys[key] = false;
    // }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    arcballCam.drag(xpos,ypos);
}

void do_movement()
{
    // Camera controls
    // if (keys[GLFW_KEY_W])
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (keys[GLFW_KEY_S])
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (keys[GLFW_KEY_A])
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (keys[GLFW_KEY_D])
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
}

// bool firstMouse = true;
// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     if (firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }
//
//     GLfloat xoffset = xpos - lastX;
//     GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
//
//     lastX = xpos;
//     lastY = ypos;
//
//     camera.ProcessMouseMovement(xoffset, yoffset);
// }

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(yoffset);
    Front -= (float)yoffset;
    if (Front < 1.0f)
        Front = 1.0f;
    else if (Front >= 100)
        Front = 100;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
