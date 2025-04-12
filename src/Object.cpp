#include "include/Object.h"

PObject::PObject(string &n, glm::vec3 pos, Camera c) :
        name(n),
        mesh(nullptr),
        camera(c) {
    this->position = pos;
}
