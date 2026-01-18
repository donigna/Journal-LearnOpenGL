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
    inline static string container2 = rootPath + "textures/container2.png";
    inline static string container2_specular = rootPath + "textures/container2_specular.png";
    inline static string awesomeface = rootPath + "textures/awesomeface.png";

    // ----------------
    // Shader Path
    // ----------------
    inline static string shader_vert = rootPath + "shaders/shader.vert";
    inline static string shader_frag = rootPath + "shaders/shader.frag";
    inline static string light_source_vert = rootPath + "shaders/light_source.vert";
    inline static string light_source_frag = rootPath + "shaders/light_source.frag";

    // ----------------
    // Model Path
    // ----------------

    // ----------------
    // Font Path
    // ----------------
};