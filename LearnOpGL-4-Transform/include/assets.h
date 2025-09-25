#pragma once
#include <string>
using namespace std;

class Assets
{
public:
    // Root Folder
    inline static string rootPath = "../assets/";

    // ----------------
    // Texture Path
    // ----------------
    inline static string container = rootPath + "textures/container.jpg";
    inline static string awesomeface = rootPath + "textures/awesomeface.png";

    // ----------------
    // Shader Path
    // ----------------
    inline static string shader_vert = rootPath + "shaders/shader.vert";
    inline static string shader_frag = rootPath + "shaders/shader.frag";
    inline static string new_shader_vert = rootPath + "shaders/new_shader.vert";

    // ----------------
    // Model Path
    // ----------------

    // ----------------
    // Font Path
    // ----------------
};