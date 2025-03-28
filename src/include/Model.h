//#ifndef MODEL_H
//#define MODEL_H
//
//
//#include "shader.h"
//#include <vector>
//#include <iostream>
//#include "Mesh.h"
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <stb_image.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <map>
//#include <vector>
//class Model {
//public:
//    Model(string path) {
//        loadModel(path);
//    }
//
//    void Draw(Shader shader) {
//        for (unsigned int i = 0; i < meshes.size(); ++i) {
//            meshes[i].Draw(shader);
//        }
//    }
//
//private:
//    vector<Mesh> meshes;
//    string directory;
//
//private:
//    vector<Texture> textures_loaded;
//    void loadModel(string path) {
//        Assimp::Importer importer;
//        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
//            cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
//            return;
//        }
//        directory = path.substr(0, path.find_last_of('/'));
//
//        proccessNode(scene->mRootNode, scene);
//    }
//
//    void proccessNode(aiNode *node, const aiScene *scene){
//        for(unsigned int i = 0; i < node->mNumMeshes; i++){
//
//            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//            meshes.push_back(processMesh(mesh, scene));
//        }
//        for(unsigned int i = 0; i < node->mNumMeshes; i++){
//
//            proccessNode(node->mChildren[i], scene);
//        }
//    }
//
//    Mesh processMesh(aiMesh *mesh, const aiScene *scene){
//        vector<Vertex> vertices;
//        vector<unsigned int> indices;
//        vector<Texture> textures;
//
//        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//            Vertex vertex;
//            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
//            // positions
//            vector.x = mesh->mVertices[i].x;
//            vector.y = mesh->mVertices[i].y;
//            vector.z = mesh->mVertices[i].z;
//            vertex.Position = vector;
//
//            if (mesh->HasNormals())
//            {
//                vector.x = mesh->mNormals[i].x;
//                vector.y = mesh->mNormals[i].y;
//                vector.z = mesh->mNormals[i].z;
//                vertex.Normal = vector;
//            }
//
//            if(mesh->mTextureCoords[0])
//            {
//                glm::vec2 vec;
//
//                vec.x = mesh->mTextureCoords[0][i].x;
//                vec.y = mesh->mTextureCoords[0][i].y;
//                vertex.TexCoords = vec;
//            }
//            else
//                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//
//            vertices.push_back(vertex);
//        }
//        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//        {
//            aiFace face = mesh->mFaces[i];
//            // retrieve all indices of the face and store them in the indices vector
//            for(unsigned int j = 0; j < face.mNumIndices; j++)
//                indices.push_back(face.mIndices[j]);
//        }
//        // process materials
//        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
//        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
//        // Same applies to other texture as the following list summarizes:
//        // diffuse: texture_diffuseN
//        // specular: texture_specularN
//        // normal: texture_normalN
//
//        // 1. diffuse maps
//        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//        // 2. specular maps
//        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//
//        // return a mesh object created from the extracted mesh data
//        return Mesh(vertices, indices, textures);
//    }
//
//    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
//        vector<Texture> textures;
//        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//        {
//            aiString str;
//            mat->GetTexture(type, i, &str);
//            bool skip = false;
//            for(unsigned int j = 0; j < textures_loaded.size(); j++)
//            {
//                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
//                {
//                    textures.push_back(textures_loaded[j]);
//                    skip = true;
//                    break;
//                }
//            }
//            if(!skip)
//            {   // if texture hasn't been loaded already, load it
//                Texture texture;
//                texture.id = TextureFromFile(str.C_Str(), directory);
//                texture.type = typeName;
//                texture.path = str.C_Str();
//                textures.push_back(texture);
//                textures_loaded.push_back(texture); // add to loaded textures
//            }
//        }
//        return textures;
//    }
//    unsigned int TextureFromFile(const char *path, const string &directory)
//    {
//        string filename = string(path);
//        filename = directory + '/' + filename;
//
//        unsigned int textureID;
//        glGenTextures(1, &textureID);
//
//        int width, height, nrComponents;
//        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//        if (data)
//        {
//            GLenum format;
//            if (nrComponents == 1)
//                format = GL_RED;
//            else if (nrComponents == 3)
//                format = GL_RGB;
//            else if (nrComponents == 4)
//                format = GL_RGBA;
//
//            glBindTexture(GL_TEXTURE_2D, textureID);
//            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//            glGenerateMipmap(GL_TEXTURE_2D);
//
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "Texture failed to load at path: " << path << std::endl;
//            stbi_image_free(data);
//        }
//
//        return textureID;
//    }
//};
//
//
//#endif
