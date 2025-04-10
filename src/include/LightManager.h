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
    string type;
    unsigned int index;
    void drawPointLight();
    void drawSpotLight(Camera cam);
    void drawDirLight();
public:
    PLight(string name, vec3 pos, Shader &shader, string type, unsigned int index);
    void Draw(Shader& s,Camera camera);
};


#endif //TESTBUILD_LIGHTMANAGER_H
