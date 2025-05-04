#include "include/GlobalVars.h"

GlobalVars::GlobalVars(Camera &cam, Shader &s1, Shader &s2) {
    camera = &cam;
    objectShader = &s1;
    lightShader = &s2;
}

Camera& GlobalVars::getCamera() {
    if (!camera) throw std::runtime_error("Camera not initialized");
    return *camera;
}

Shader& GlobalVars::getObjectShader() {
    if (!objectShader) throw std::runtime_error("Object shader not initialized");
    return *objectShader;
}

 Shader& GlobalVars::getLightShader() {
    if (!lightShader) throw std::runtime_error("Light shader not initialized");
    return *lightShader;
}

void GlobalVars::logGlobalInfo() {
    std::cout << "CAMERA: " << camera->Position.x << "\n";
    std::cout << "OBJECT ID: " << objectShader->ID << "\n";
    std::cout << "LIGHT ID: " << lightShader->ID << "\n";
}