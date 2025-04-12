#ifndef TESTBUILD_OBJECT_H
#define TESTBUILD_OBJECT_H
#include "string"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "include/Mesh.h"
using namespace std;
using namespace glm;

class PObject{
public:
    PObject(string n, vec3 pos, Mesh &mesh);

    string& name;
    vec3 position;
    Mesh* mesh;
    Camera& camera;
    PObject(string& n, vec3 pos, Camera c);
    void meshDraw();
};

#endif
