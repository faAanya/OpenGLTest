#ifndef TESTBUILD_GLOBALVARS_H
#define TESTBUILD_GLOBALVARS_H

#include "Camera.h"
#include "Shader.h"

class GlobalVars {
private:
    Camera *camera;
    Shader *objectShader;
    Shader *lightShader;

public:
    GlobalVars(Camera &cam, Shader &s1, Shader &s2);

    Camera &getCamera();

    Shader &getObjectShader();

    Shader &getLightShader();

    void logGlobalInfo();
};

#endif
