#include "include/PObject.h"

PObject::PObject(string n, Camera &c, glm::vec3 pos, glm::vec3 scale = vec3(1.0f, 1.0f, 1.0f), float angle = 0.0f,
                 string t = "obj") :
        name(n),
        mesh(nullptr),
        camera(c) {
    this->position = pos;
    this->scale = scale;
    this->angle = angle;

    isDrawing = true;
}

void PObject::deleteObj() {
    isDrawing = false;
}
