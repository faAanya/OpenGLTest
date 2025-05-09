#ifndef TESTBUILD_POBJECT_H
#define TESTBUILD_POBJECT_H
#include "string"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "include/Mesh.h"
using namespace std;
using namespace glm;

class PObject{
public:
    PObject() = default;

    string name;
    string& type;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float cutOff = 12.5f;
    float outerCutOff = 15.0f;

    vec3 position;
    vec3 color;
    float angle;
    vec3 scale;
    Mesh* mesh;
    Camera& camera;
    bool isDrawing;
    PObject(string n, Camera& c, glm::vec3 pos,string& t, glm::vec3 scale,float angle);

    void drawMesh();
    void deleteObj();




};

#endif
