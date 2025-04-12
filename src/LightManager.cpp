#include "include/LightManager.h"
#include "include/shader.h"
#include "include/Camera.h"
#include "include/verts.h"
#include <string>

PLight::PLight(string name, vec3 pos, Camera cam, Shader &shader, Shader &light, string t, unsigned int index)
        : PObject(name, pos, cam),
          objectToLight(shader),
          light(light),
          type(t),
          index(index) {


    mesh = new Mesh(verts::sphere(1.0f, 36, 18));
}

void PLight::Draw(Shader &s, Camera& c) {
    if (type == "point") {
        drawPointLight(s,c);
    } else if (type == "spot") {
        drawSpotLight(s, c);
    } else if (type == "directional") {
        drawDirLight(s,c);
    }

}

void PLight::meshDraw() {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.1f));
    light.setMat4("model", model);

    mesh->Draw(light, camera);
}

void PLight::drawPointLight(Shader &s, Camera& c) {

    string name = "pointLights[" + to_string(index) + "]";
    s.setVec3(name + ".position", position);
    s.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    s.setVec3(name + ".diffuse", 0.8f, 0.8f, 0.8f);
    s.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    s.setFloat(name + ".constant", 1.0f);
    s.setFloat(name + ".linear", 0.09f);
    s.setFloat(name + ".quadratic", 0.032f);
    s.setBool(name + ".enabled", true);

}

void PLight::drawSpotLight(Shader &s,  Camera& c) {


    string name = "spotLights[" + to_string(index) + "]";

    s.setVec3(name + ".position", c.Position);
    s.setVec3(name + ".direction", c.Front);
    s.setFloat(name + ".cutOff", glm::cos(glm::radians(12.5f)));
    s.setFloat(name + ".outerCutOff", glm::cos(glm::radians(15.0f)));
    s.setFloat(name + ".constant", 1.0f);
    s.setFloat(name + ".linear", 0.09f);
    s.setFloat(name + ".quadratic", 0.032f);
    s.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    s.setVec3(name + ".diffuse", 1.0f, 1.0f, 1.0f);
    s.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    s.setBool(name + ".enabled", true);

}

void PLight::drawDirLight(Shader &s, Camera& c) {
    string name = "dirLights[" + to_string(index) + "]";
    s.setVec3(name + ".direction", position);
    s.setVec3(name + ".ambient", 0.2f, 0.2f, 0.2f);
    s.setVec3(name + ".diffuse", 0.5f, 0.5f, 0.5f);
    s.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    s.setBool(name + ".enabled", true);
}
