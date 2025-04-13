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
    void drawPointLight();
    void drawSpotLight();
    void drawDirLight();
public:
    PLight(string name, Camera& cam, vec3 pos, vec3 scale, float angle, Shader &shader, Shader &light, string t,
           unsigned int index);
    void meshDraw();
    void Draw();

};


#endif //TESTBUILD_LIGHTMANAGER_H
