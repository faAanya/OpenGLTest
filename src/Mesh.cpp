#include "include/Mesh.h"
#include "include/EBO.h"
#include "include/VBO.h"
#include "include/VAO.h"
#include "include/Camera.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> &textures) {

    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO.bindVAO();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void *) 0);
    VAO.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void *) (3 * (sizeof(float))));
    VAO.LinkVBO(VBO, 2, 2, sizeof(Vertex), (void *) (6 * (sizeof(float))));

    VAO.unBindVAO();
    VBO.unBindVBO();
    EBO.unBindEBO();
}

Mesh::Mesh(vector<Vertex> vertices, vector<Texture> &textures) {

    Mesh::vertices = vertices;
    Mesh::textures = textures;

    VAO.bindVAO();

    VBO VBO(vertices);

    VAO.LinkVBO(VBO, 0, 3, sizeof(Vertex), (void *) 0);
    VAO.LinkVBO(VBO, 1, 3, sizeof(Vertex), (void *) (3 * (sizeof(float))));
    VAO.LinkVBO(VBO, 2, 2, sizeof(Vertex), (void *) (6 * (sizeof(float))));

    VAO.unBindVAO();
    VBO.unBindVBO();
}

void Mesh::Draw(Shader& shader,
                Camera& camera,
                glm::mat4 matrix,
                glm::vec3 translation,
                glm::quat rotation,
                glm::vec3 scale) {
    shader.use();

    VAO.bindVAO();

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
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }

    shader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    // Push the matrices to the vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}