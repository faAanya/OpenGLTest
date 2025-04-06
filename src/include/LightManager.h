#ifndef TESTBUILD_LIGHTMANAGER_H
#define TESTBUILD_LIGHTMANAGER_H

#include "shader.h"
#include "vector"
using namespace std;
class LightCreator {
private:
    Shader &lightShader;

public:
    LightCreator(Shader &shader);

};


#endif //TESTBUILD_LIGHTMANAGER_H
