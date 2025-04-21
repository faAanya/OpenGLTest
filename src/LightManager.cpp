#include "include/LightManager.h"
#include "include/shader.h"
#include "include/Camera.h"
#include "include/verts.h"
#include <string>

PLight::PLight(string name, Camera &cam, vec3 pos, vec3 scale, float angle, Shader &shader, Shader &light, string t,
               unsigned int index)
        : PObject(name, cam, pos, scale, angle),
          objectToLight(shader),
          light(light),
          type(t),
          index(index) {


//    size_t vertexCount = 0;
//    Vertex* sphereVertices = verts::sphere(1.0f, 32, 32, vertexCount);
//    vector<Vertex> vert(sphereVertices, sphereVertices + vertexCount);
    vector<Vertex> vert(verts::pyramid, verts::pyramid + sizeof(verts::pyramid) / sizeof(Vertex));
    mesh = new Mesh(vert);
}

void PLight::Draw() {
    if (type == "point") {
        drawPointLight();
    } else if (type == "spot") {
        drawSpotLight();
    } else if (type == "directional") {
        drawDirLight();
    }

}

void PLight::meshDraw() {

    light.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 1280 / (float) 720, 0.1f,
                                            100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    light.setMat4("projection", projection);
    light.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.1f));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
    light.setMat4("model", model);

    mesh->Draw(light, camera);
}

void PLight::drawPointLight() {


    string name = "pointLights[" + to_string(index) + "]";
    objectToLight.setVec3(name + ".position", position);
    objectToLight.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    objectToLight.setVec3(name + ".diffuse", 0.8f, 0.8f, 0.8f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);
    objectToLight.setBool(name + ".enabled", true);

}

void PLight::drawSpotLight() {
    string name = "spotLights[" + to_string(index) + "]";

    objectToLight.setVec3(name + ".position", camera.Position);
    objectToLight.setVec3(name + ".direction", camera.Front);
    objectToLight.setFloat(name + ".cutOff", glm::cos(glm::radians(12.5f)));
    objectToLight.setFloat(name + ".outerCutOff", glm::cos(glm::radians(15.0f)));
    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);
    objectToLight.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    objectToLight.setVec3(name + ".diffuse", 1.0f, 1.0f, 1.0f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setBool(name + ".enabled", true);

}

void PLight::drawDirLight() {
    string name = "dirLights[" + to_string(index) + "]";
    objectToLight.setVec3(name + ".direction", position);
    objectToLight.setVec3(name + ".ambient", 0.2f, 0.2f, 0.2f);
    objectToLight.setVec3(name + ".diffuse", 0.5f, 0.5f, 0.5f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setBool(name + ".enabled", true);
}
