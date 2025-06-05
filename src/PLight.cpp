#include <glm/glm.hpp>
#include "include/PLight.h"
#include "include/Shader.h"
#include "include/Camera.h"
#include "include/verts.h"
#include <string>



PLight::PLight(string name, Camera &cam, vec3 pos, vec3 scale, vec3 angle, Shader &shader, Shader &light, string t,
               unsigned int index)
        : PObject(name, cam, pos, t, scale, angle),
          objectToLight(shader),
          light(light),
          index(index) {

    direction = glm::vec3(0, 0, 0);
    ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);
    color = glm::vec3(0.0, 0.0, 0.0);
    vector<Vertex> vert(verts::sphere, verts::sphere + sizeof(verts::sphere) / sizeof(Vertex));
    mesh = new Mesh(vert);

}

void PLight::Draw() {
    if (isDrawing) {
        if (type == "point") {
            drawPointLight();
        } else if (type == "spot") {
            drawSpotLight();
        } else if (type == "directional") {
            drawDirLight();
        }
        drawMesh();
    }
}

void PLight::drawMesh() {

    light.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 1280 / (float) 720, 0.1f,
                                            100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    light.setMat4("projection", projection);
    light.setMat4("view", view);
    light.setVec3("color", glm::vec3(1.0, 1.0, 1.0) - color);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
    light.setMat4("model", model);

    mesh->Draw(light, camera);
}

void PLight::drawPointLight() {
    string name = "pointLights[" + to_string(index) + "]";
    objectToLight.setVec3(name + ".position", position);

    objectToLight.setVec3(name + ".ambient", ambient);
    objectToLight.setVec3(name + ".diffuse", diffuse);
    objectToLight.setVec3(name + ".specular", specular);

    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);
    objectToLight.setBool(name + ".enabled", isDrawing);

    objectToLight.setVec3("material.lightColor", color);
}

void PLight::drawSpotLight() {
    string name = "spotLights[" + to_string(index) + "]";

    objectToLight.setVec3(name + ".position", position);
    objectToLight.setVec3(name + ".direction", direction - position);
    objectToLight.setFloat(name + ".cutOff", glm::cos(glm::radians(cutOff)));
    objectToLight.setFloat(name + ".outerCutOff", glm::cos(glm::radians(outerCutOff)));

    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);

    objectToLight.setVec3(name + ".ambient", ambient);
    objectToLight.setVec3(name + ".diffuse", diffuse);
    objectToLight.setVec3(name + ".specular", specular);

    objectToLight.setBool(name + ".enabled", isDrawing);
    objectToLight.setVec3("material.lightColor", color);
}

void PLight::drawDirLight() {
    string name = "dirLights[" + to_string(index) + "]";
    objectToLight.setVec3(name + ".direction", direction - position);

    objectToLight.setVec3(name + ".ambient", ambient);
    objectToLight.setVec3(name + ".diffuse", diffuse);
    objectToLight.setVec3(name + ".specular", specular);

    objectToLight.setBool(name + ".enabled", isDrawing);
    objectToLight.setVec3("material.lightColor", color);
}
