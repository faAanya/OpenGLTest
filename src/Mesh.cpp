#include "include/Mesh.h"
#include "include/EBO.h"
#include "include/VBO.h"
#include "include/VAO.h"
#include "include/Camera.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> &textures) {

    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vao.bindVAO();

    VBO VBO(vertices);
    EBO EBO(indices);

    vao.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void *) 0);
    vao.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void *) (3 * (sizeof(float))));
    vao.LinkVBO(VBO, 2, 2, sizeof(Vertex), (void *) (6 * (sizeof(float))));

    vao.unBindVAO();
    VBO.unBindVBO();
    EBO.unBindEBO();
}

Mesh::Mesh(vector<Vertex> vertices, vector<Texture> &textures) {

    Mesh::vertices = vertices;
    Mesh::textures = textures;

    vao.bindVAO();

    VBO VBO(vertices);

    vao.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void *) 0);
    vao.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void *) (3 * (sizeof(float))));
    vao.LinkVBO(VBO, 2, 2, sizeof(Vertex), (void *) (6 * (sizeof(float))));

    vao.unBindVAO();
    VBO.unBindVBO();
}

Mesh::Mesh(vector<Vertex> vertices) {

    Mesh::vertices = vertices;

    vao.bindVAO();

    VBO VBO(vertices);

    vao.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void *) 0);
    vao.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void *) (3 * (sizeof(float))));
    vao.LinkVBO(VBO, 2, 2, sizeof(Vertex), (void *) (6 * (sizeof(float))));

    vao.unBindVAO();
    VBO.unBindVBO();
}

void Mesh::Draw(Shader &shader, Camera &camera) {
    shader.use();

    vao.bindVAO();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (int i = 0; i < textures.size(); ++i) {
        std::string num;
        std::string type = textures[i].type;

        if (type == "diffuse") {
            num = std::to_string(numDiffuse++);
        } else if (type == "specular") {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(),i);
        textures[i].Bind();
    }
    shader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}