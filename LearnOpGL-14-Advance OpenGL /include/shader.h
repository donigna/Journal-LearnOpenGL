#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{

public:
    // The program ID
    uint ID;
    // Constructor reads and builds the shader
    Shader(const char *vertexPath = nullptr, const char *fragmentPath = nullptr, const char *geometryPath = nullptr)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        // ensure ifstream objectscan throw exception
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {

            // open file
            if (vertexPath != nullptr)
            {
                std::stringstream vShaderStream;
                vShaderFile.open(vertexPath);
                vShaderStream << vShaderFile.rdbuf();
                vShaderFile.close();
                vertexCode = vShaderStream.str();
            }

            if (fragmentPath != nullptr)
            {
                std::stringstream fShaderStream;
                fShaderFile.open(fragmentPath);
                fShaderStream << fShaderFile.rdbuf();
                fShaderFile.close();
                fragmentCode = fShaderStream.str();
            }

            if (geometryPath != nullptr)
            {
                gShaderFile.open(geometryCode);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        // Compile Shader
        uint vertex, fragment;

        // Vertex Shader
        if (vertexPath != nullptr)
        {
            const char *vShaderCode = vertexCode.c_str();
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            CheckCompileErrors(vertex, "VERTEX");
        }

        // Fragment Shader
        if (fragmentPath != nullptr)
        {
            const char *fShaderCode = fragmentCode.c_str();
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            CheckCompileErrors(fragment, "FRAGMENT");
        }


        // if geometry shader is given, compile geometry shader
        GLuint geometry;
        if (geometryPath != nullptr)
        {
            const char* gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");
        }

        // Shader Program
        ID = glCreateProgram();
        if (vertexPath != nullptr)
            glAttachShader(ID, vertex);
        if (fragmentPath != nullptr)
            glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");


        // delete created shader as they're linked into program now and no longer necessery
        if (vertexPath != nullptr)
            glDeleteShader(vertex);
        if (fragmentPath != nullptr)
            glDeleteShader(fragment);
        if (geometryPath != nullptr)
            glDeleteShader(geometry);
    };
    // Use the program
    void Use() { glUseProgram(ID); }
    inline void SetMat4(const std::string &name,const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    inline void SetVec3(const std::string &name,const glm::vec3 &vec) const
    {
        glUniform3f(glGetUniformLocation(ID,name.c_str()), vec.x, vec.y, vec.z);
    }

private :
    // utility function to check shader compilation/linking errors.
    void CheckCompileErrors(uint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n ---------------------------" << "\n";
            }
        } else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n ---------------------------" << "\n";
            }
        }
    }
};

#endif