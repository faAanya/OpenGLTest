#include "include/PObject.h"

PObject::PObject(string n, Camera &c, glm::vec3 pos, string &t, glm::vec3 scale = vec3(1.0f, 1.0f, 1.0f), vec3 angle = vec3(0.0f, 0.0f, 0.0f)) :
        name(n),
        mesh(nullptr),
        type(t),
        camera(c) {
    this->position = pos;
    this->scale = scale;
    this->angle = angle;

    isDrawing = true;
}

void PObject::deleteObj() {
    isDrawing = false;
}
