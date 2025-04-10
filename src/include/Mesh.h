#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "Camera.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;
using namespace glm;

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    VAO VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
         vector<Texture> &textures);
    Mesh(vector<Vertex> vertices, vector<Texture>& textures);


    void Draw(Shader& shader,
              Camera& camera,
              glm::mat4 matrix = glm::mat4(1.0f),
              glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
              glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif
