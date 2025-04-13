#ifndef TESTBUILD_FIGUREMANAGER_H
#define TESTBUILD_FIGUREMANAGER_H

#include "include/Object.h"
#include "include/LightManager.h"

class PFigure : public PObject {
private:
    Shader &object;
    std::vector<PLight> lights;
    string type;
    unsigned int index;

public:
    PFigure(string name, Camera& cam, vec3 pos, vec3 scale, float angle, Shader &shader, string t,
            unsigned int index);

    void Draw(Shader &s);
};

#endif
