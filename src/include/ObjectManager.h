#ifndef TESTBUILD_OBJECTMANAGER_H
#define TESTBUILD_OBJECTMANAGER_H

#include "PFigure.h"
#include "PLight.h"
#include <GLFW/glfw3.h>
#include "include/shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "include/Camera.h"
#include "include/VBO.h"
#include "include/PLua.h"
#include "include/Texture.h"

using namespace std;

class ObjectManager {

private:
    vector<PLight> lights;
    vector<PFigure> figures;
    PObject* activeObject = nullptr;

    bool hasActiveObject = false;
    int lightCounter = 0;

public:

    bool stopDrawingAll = false;

    ObjectManager() = default;


    void createLight(std::string name, Camera& cam, glm::vec3 pos,
                     glm::vec3 scale, float angle, Shader& shader,
                     Shader& lightShader, std::string type) {
        lights.emplace_back(name, cam, pos, scale, angle,
                            shader, lightShader, type, lightCounter);

        lightCounter++;
    }


    void createFigure(std::string name, Camera& cam, glm::vec3 pos,
                      glm::vec3 scale, float angle, Shader& shader,
                      std::string type,
                      std::vector<Texture>& textures) {
        figures.emplace_back(name, cam, pos, scale, angle,
                             shader, type, textures);
    }


    void drawAll() {

        if(!stopDrawingAll){
            for(auto& figure : figures) {
                figure.Draw();
            }

            for(auto& light : lights) {
                light.Draw();
            }
        }
    }

    PObject* getActiveObject() const {
        return activeObject;
    }

    bool selectObjectByName(const std::string& targetName) {

        if(!hasActiveObject){
            activeObject = nullptr;
            for(auto& figure : figures) {
                if(figure.name == targetName) {
                    activeObject = &figure;
                    return true;
                }
            }

            for(auto& light : lights) {
                if(light.name== targetName) {
                    activeObject = &light;
                    return true;
                }
            }

            return false;
        }

    }

    void deleteAllObjects(){
        stopDrawingAll = true;
    }

};

#endif
