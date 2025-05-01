#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
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
    Mesh(vector<Vertex> vertices);


    void Draw(Shader &shader, Camera& camera);
};

#endif
