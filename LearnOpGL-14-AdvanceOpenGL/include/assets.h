#pragma once
#include <string>

class Assets
{
public:
    // Root Folder
    inline static std::string rootPath = "../assets/";

    // ----------------
    // Texture Path
    // ----------------
    inline static std::string container = rootPath + "textures.fbm/container.jpg";
    inline static std::string container2 = rootPath + "textures.fbm/container2.png";
    inline static std::string container2_specular = rootPath + "textures.fbm/container2_specular.png";
    inline static std::string awesomeface = rootPath + "textures.fbm/awesomeface.png";

    // ----------------
    // Shader Path
    // ----------------
    inline static std::string shader_vert = rootPath + "shaders/shader.vert";
    inline static std::string shader_frag = rootPath + "shaders/shader.frag";
    inline static std::string light_source_vert = rootPath + "shaders/light_source.vert";
    inline static std::string light_source_frag = rootPath + "shaders/light_source.frag";

    // ----------------
    // Model Path
    // ----------------

    // ----------------
    // Font Path
    // ----------------
};