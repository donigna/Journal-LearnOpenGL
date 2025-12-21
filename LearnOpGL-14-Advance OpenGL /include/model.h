#ifndef MYAPP_MODEL_H
#define MYAPP_MODEL_H
#include "mesh.h"
#include "shader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

class Model
{
    public:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;
        Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
        {
            loadModel(path);
        };
        void Draw(Shader &shader);
private:
    void loadModel(std::string const &path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene);
};

#endif //MYAPP_MODEL_H