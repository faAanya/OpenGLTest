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
    float angle;
    vec3 scale;
    Mesh* mesh;
    Camera& camera;
    PObject(string &n, Camera& c, glm::vec3 pos, glm::vec3 scale,float angle);
    void meshDraw();

    void moveTo(vec3 newPos);
    void changeLightColor();
    void scaleTo(vec3 newScale);
    void rotateTo(vec3 newAngle);

};

#endif
