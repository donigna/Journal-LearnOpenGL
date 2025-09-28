// --- INCLUDE EXTERNAL ---
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// --- INCLUDE INTERNAL ---
#include <assets.h>
#include <camera.hpp>
#include <shader.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Input
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
void do_movement();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 1;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);    // kamera di depan cube
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // menghadap ke -Z
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // atas normal

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = SCR_WIDTH / 2.0;
GLfloat lastY = SCR_HEIGHT / 2.0;
GLfloat fov = 45.0f;

Camera cam(cameraPos);
bool keys[1024];

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;

int main()
{

    /// ########### FIrst Tutorial matrix
    // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); // define the vector
    // glm::mat4 trans = glm::mat4(1.0f); // define transformation matrix with matrix identity 4x4 as default
    // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // add translation to transformation matrix
    // vec = trans * vec; // multiply transformation matrix with vector

    // // output of vector after multiplication
    // cout << vec.x
    //      << vec.y
    //      << vec.z << endl;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL - 6 - Camera", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.3f);
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // shader
    // --------------------
    Shader ourShader(Assets::shader_vert.c_str(), Assets::shader_frag.c_str());
    int mixLoc = glGetUniformLocation(ourShader.Program, "ourMix");

    // buffer
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // texture

    // create references
    // bind texture 1
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // ## EXERCISE 2
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Note that we set our container wrapping method to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Note that we set our container wrapping method to GL_REPEAT
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char *image1 = SOIL_load_image(Assets::container.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    // load texture and set mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Free space from texture 1
    SOIL_free_image_data(image1);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // ## EXERCISE 2
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // We want to repeat this pattern so we set kept it at GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // We want to repeat this pattern so we set kept it at GL_REPEAT
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *image2 = SOIL_load_image(Assets::awesomeface.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    // load texture and set mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);

    glGenerateMipmap(GL_TEXTURE_2D);

    if (image1 == NULL)
    {
        cout << "Gagal memuat tekstur container!" << endl;
    }

    // Free space from texture 1
    SOIL_free_image_data(image2);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");

    // Lighting
    // -----------
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    Shader lampShader(Assets::light_source_vert.c_str(), Assets::light_source_frag.c_str());
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        glfwPollEvents();
        do_movement();

        // render
        // ------

        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glUniform1f(mixLoc, mixValue);
        ourShader.Use();

        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

        GLuint objectColorLoc = glGetUniformLocation(ourShader.Program, "objectColor");
        GLuint lightColorLoc = glGetUniformLocation(ourShader.Program, "lightColor");
        GLint lightPosLoc = glGetUniformLocation(ourShader.Program, "lightPos");
        GLint viewPosLoc = glGetUniformLocation(ourShader.Program, "viewPos");
        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, cam.Position.x, cam.Position.y, cam.Position.z);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(cam.Zoom), GLfloat(SCR_WIDTH) / GLfloat(SCR_HEIGHT), 0.1f, 100.0f);
        glm::mat4 view = cam.GetViewMatrix();
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(.5f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projectionLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lampShader.Use();

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projectionLoc = glGetUniformLocation(lampShader.Program, "projection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void do_movement()
{
    // Camera controls
    // GLfloat cameraSpeed = 5.0f * deltaTime;
    // if (keys[GLFW_KEY_W])
    //     cameraPos += cameraSpeed * cameraFront;
    // if (keys[GLFW_KEY_S])
    //     cameraPos -= cameraSpeed * cameraFront;
    // if (keys[GLFW_KEY_A])
    //     cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // if (keys[GLFW_KEY_D])
    //     cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // New movement
    if (keys[GLFW_KEY_W])
        cam.ProccessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        cam.ProccessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        cam.ProccessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        cam.ProccessKeyboard(RIGHT, deltaTime);
}

// bool firstMouse = true;
// void mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//     static bool firstMouse = true;
//     if (firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; // dibalik supaya arah naik/turun normal
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.1f;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw += xoffset;
//     pitch += yoffset;

//     // clamp pitch biar gak kebalik
//     if (pitch > 89.0f)
//         pitch = 89.0f;
//     if (pitch < -89.0f)
//         pitch = -89.0f;

//     // hitung front baru
//     glm::vec3 front;
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     cameraFront = glm::normalize(front);
// }

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // dibalik supaya arah naik/turun normal
    lastX = xpos;
    lastY = ypos;

    cam.ProccessMouseMovement(xoffset, yoffset);
}

// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//     if (fov >= 1.0f && fov <= 45.0f)
//         fov -= yoffset;
//     if (fov <= 1.0f)
//         fov = 1.0f;
//     if (fov >= 45.0f)
//         fov = 45.0f;
// }

glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -position.x;         // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    cam.ProccessMouseScroll(yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}