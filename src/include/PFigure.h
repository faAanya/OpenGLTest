#ifndef TESTBUILD_PFIGURE_H
#define TESTBUILD_PFIGURE_H

#include "include/PObject.h"
#include "include/PLight.h"

class PFigure : public PObject {
private:
    Shader &object;
    std::vector<PLight> lights;
    std::vector<Texture> textures;
    unsigned int index;

public:
    PFigure(string name, Camera &cam, vec3 pos, vec3 scale, vec3 angle, Shader &shader, string t,
            const std::vector<std::string> &texturePaths);
    std::vector<Vertex> currentVertices;

    void updateMeshWithCurrentVertices();
    void Draw();
    std::vector<Texture> createTexturesFromPaths(const std::vector<std::string>& texturePaths);
    void addTexture(const std::string& texturePath, const std::string& textureType);
    void createMesh(string t);
    void updateMesh(const std::vector<Vertex>& newVertices);

    void removeAllTextures();
};

#endif
