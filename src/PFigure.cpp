#include <algorithm>
#include "include/PFigure.h"
#include "include/Texture.h"
#include "include/verts.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

PFigure::PFigure(string name, Camera &cam, vec3 pos, vec3 scale, float angle, Shader &shader, string t,
                 const std::vector<std::string> &texturePaths) :
        PObject(name, cam, pos, t, scale, angle),
        object(shader) {

    textures = createTexturesFromPaths(texturePaths);
    createMesh(t);

    color = glm::vec3(0.0, 0.0, 0.0);

}
void PFigure::updateMeshWithCurrentVertices() {
    if (mesh) {
        delete mesh;
    }
    mesh = new Mesh(currentVertices, textures);
}
void PFigure::updateMesh(const std::vector<Vertex>& newVertices) {
    if (mesh) {
        delete mesh; // Удаляем старый меш
    }
    mesh = new Mesh(newVertices, textures);
}

void PFigure::createMesh(string t) {
    if (t == "plane") {
        vector<Vertex> vert(verts::plane, verts::plane + sizeof(verts::plane) / sizeof(Vertex));
        mesh = new Mesh(vert, textures);
        currentVertices = vert;
        return;
    } else if (t == "cube") {
        vector<Vertex> vert(verts::cube, verts::cube + sizeof(verts::cube) / sizeof(Vertex));
        mesh = new Mesh(vert, textures);
        currentVertices = vert;
        return;
    } else if (t == "pyramid") {
        vector<Vertex> vert(verts::pyramid, verts::pyramid + sizeof(verts::pyramid) / sizeof(Vertex));
        mesh = new Mesh(vert, textures);
        currentVertices = vert;
        return;
    } else if (t == "sphere") {
        vector<Vertex> vert(verts::sphere, verts::sphere + sizeof(verts::sphere) / sizeof(Vertex));
        mesh = new Mesh(vert, textures);
        currentVertices = vert;
        return;
    } else if (t == "cylinder") {
        vector<Vertex> vert(verts::cylinder, verts::cylinder + sizeof(verts::cylinder) / sizeof(Vertex));
        mesh = new Mesh(vert, textures);
        currentVertices = vert;
        return;
    } else {
        cout << "Wrong object type" << t;
    }
}

void PFigure::Draw() {
    if (isDrawing) {
        object.use();
        object.setVec3("viewPos", camera.Position);
        object.setVec3("material.objectColor", color);
        object.setFloat("material.shininess", 32.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 1280 / (float) 720, 0.1f,
                                                100.0f);
        object.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();

        object.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
        object.setMat4("model", model);

        mesh->Draw(object, camera);
    }
}

std::vector<Texture> PFigure::createTexturesFromPaths(const std::vector<std::string> &texturePaths) {
    std::vector<Texture> textures;

    if (texturePaths.empty()) {
        textures.emplace_back("resources/textures/pixel.png", "diffuse", GL_TEXTURE0);
        return textures;
    }

    for (size_t i = 0; i < texturePaths.size(); ++i) {
        if (!texturePaths[i].empty()) {
            std::string texType;
            GLenum texUnit;

            if (i == 0) {
                texType = "diffuse";
                texUnit = GL_TEXTURE0;
            } else if (i == 1) {
                texType = "specular";
                texUnit = GL_TEXTURE1;
            }

            textures.emplace_back(texturePaths[i].c_str(), texType.c_str(), texUnit);
        }
    }

    return textures;
}

void PFigure::addTexture(const std::string& texturePath, const std::string& textureType) {
    GLenum texUnit;
    if (textureType == "diffuse") {
        texUnit = GL_TEXTURE0;
    } else if (textureType == "specular") {
        texUnit = GL_TEXTURE1;
    } else {
        std::cerr << "Unknown texture type: " << textureType << std::endl;
        return;
    }

    // Удаляем старую текстуру такого же типа, если есть
    textures.erase(
            std::remove_if(textures.begin(), textures.end(),
                           [&textureType](const Texture& tex) {
                               return tex.type == textureType;
                           }),
            textures.end()
    );

    textures.emplace_back(texturePath.c_str(), textureType.c_str(), texUnit);
    updateMeshWithCurrentVertices(); // Обновляем меш
}