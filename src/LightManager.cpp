#include "include/LightManager.h"
#include "include/shader.h"
#include <cstdio>
#include "include/Camera.h"
#include <string>

PLight::PLight(std::string name, glm::vec3 pos, Shader &shader, std::string t, unsigned int index) :
PObject(name, pos),
lightShader(shader),
type(t) {
}

void PLight::Draw(Camera cam) {
    if (type == "point") {
        drawPointLight();
    } else if (type == "spot") {
        drawSpotLight(cam);
    } else if (type == "directional") {
        drawDirLight();
    }
}



void PLight::drawPointLight() {

    string name = "pointLights[" + to_string(index) + "]";

    lightShader.setVec3(name + ".position", position);
    lightShader.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    lightShader.setVec3(name + ".diffuse", 0.8f, 0.8f, 0.8f);
    lightShader.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    lightShader.setFloat(name + ".constant", 1.0f);
    lightShader.setFloat(name + ".linear", 0.09f);
    lightShader.setFloat(name + ".quadratic", 0.032f);
    lightShader.setBool(name + ".enabled", true);

}

void PLight::drawSpotLight(Camera cam) {

    string name = "spotLights[" + to_string(0) + "]";
    lightShader.setVec3(name + ".position", cam.Position);
    lightShader.setVec3(name + ".direction", cam.Front);
    lightShader.setFloat(name + ".cutOff", glm::cos(glm::radians(12.5f)));
    lightShader.setFloat(name + ".outerCutOff", glm::cos(glm::radians(15.0f)));
    lightShader.setFloat(name + ".constant", 1.0f);
    lightShader.setFloat(name + ".linear", 0.09f);
    lightShader.setFloat(name + ".quadratic", 0.032f);
    lightShader.setVec3(name + ".ambient", 0.0f, 0.0f, 0.0f);
    lightShader.setVec3(name + ".diffuse", 1.0f, 1.0f, 1.0f);
    lightShader.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    lightShader.setBool(name + ".enabled", true);

}

void PLight::drawDirLight() {
    string name = "dirLights[" + to_string(0) + "]";
    lightShader.setVec3(name + ".direction", position);
    lightShader.setVec3(name + ".ambient", 0.2f, 0.2f, 0.2f);
    lightShader.setVec3(name + ".diffuse", 0.5f, 0.5f, 0.5f);
    lightShader.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    lightShader.setBool(name + ".enabled", true);
}
