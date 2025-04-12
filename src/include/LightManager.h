#ifndef TESTBUILD_LIGHTMANAGER_H
#define TESTBUILD_LIGHTMANAGER_H

#include "shader.h"
#include "vector"
#include "string"
#include "Object.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
using namespace std;
using namespace glm;

class PLight : public PObject {
private:
    Shader &objectToLight;
    Shader &light;
    string type;
    unsigned int index;
    void drawPointLight(Shader& s, Camera& c);
    void drawSpotLight(Shader& s,  Camera& c);
    void drawDirLight(Shader& s, Camera& c);
public:
    PLight(string name, vec3 pos,Camera camera, Shader &shader,Shader& light, string type, unsigned int index);
    void meshDraw();
    void Draw(Shader& s, Camera& c);

};


#endif //TESTBUILD_LIGHTMANAGER_H
