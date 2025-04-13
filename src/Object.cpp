#include "include/Object.h"

PObject::PObject(string &n, Camera& c, glm::vec3 pos, glm::vec3 scale = vec3(1.0f,1.0f, 1.0f), float angle = 0.0f) :
        name(n),
        mesh(nullptr),
        camera(c) {
    this->position = pos;
    this->scale = scale;
    this->angle = angle;

}

void PObject::moveTo(vec3 newPos) {
    this->position = newPos;

    cout<<"move";
}

void PObject::scaleTo(vec3 newScale) {}

void PObject::rotateTo(vec3 newAngle) {}