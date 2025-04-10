#include "include/LightManager.h"
#include "include/shader.h"
#include <cstdio>
#include "include/Camera.h"
#include "include/verts.h"
#include <string>

PLight::PLight(string name, vec3 pos, Shader &shader, string t, unsigned int index)
        : PObject(name, pos),
          objectToLight(shader),
          type(t),
          index(index) {
}

void PLight::Draw(Shader& s,Camera cam) {
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

    objectToLight.setVec3(name + ".position", position);
    objectToLight.setVec3(name + ".ambient", 0.05f, 0.05f, 0.05f);
    objectToLight.setVec3(name + ".diffuse", 0.8f, 0.8f, 0.8f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);
    objectToLight.setBool(name + ".enabled", true);

}

void PLight::drawSpotLight(Camera cam) {

    string name = "spotLights[" + to_string(0) + "]";
    objectToLight.setVec3(name + ".position", cam.Position);
    objectToLight.setVec3(name + ".direction", cam.Front);
    objectToLight.setFloat(name + ".cutOff", glm::cos(glm::radians(12.5f)));
    objectToLight.setFloat(name + ".outerCutOff", glm::cos(glm::radians(15.0f)));
    objectToLight.setFloat(name + ".constant", 1.0f);
    objectToLight.setFloat(name + ".linear", 0.09f);
    objectToLight.setFloat(name + ".quadratic", 0.032f);
    objectToLight.setVec3(name + ".ambient", 0.0f, 0.0f, 0.0f);
    objectToLight.setVec3(name + ".diffuse", 1.0f, 1.0f, 1.0f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setBool(name + ".enabled", true);

}

void PLight::drawDirLight() {
    string name = "dirLights[" + to_string(0) + "]";
    objectToLight.setVec3(name + ".direction", position);
    objectToLight.setVec3(name + ".ambient", 0.2f, 0.2f, 0.2f);
    objectToLight.setVec3(name + ".diffuse", 0.5f, 0.5f, 0.5f);
    objectToLight.setVec3(name + ".specular", 1.0f, 1.0f, 1.0f);
    objectToLight.setBool(name + ".enabled", true);
}
