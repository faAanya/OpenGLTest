#include "include/Object.h"

PObject::PObject(string& n, glm::vec3 pos) : name(n) {
    this->position = pos;
}