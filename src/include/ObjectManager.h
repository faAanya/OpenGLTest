#ifndef TESTBUILD_OBJECTMANAGER_H
#define TESTBUILD_OBJECTMANAGER_H

#include "PFigure.h"
#include "PLight.h"
#include "include/Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "include/Camera.h"
#include "include/VBO.h"
#include "include/Texture.h"
#include <memory>
#include <vector>

using namespace std;

class ObjectManager {

private:

    PObject *activeObject = nullptr;

    int lightCounter = 0;

public:
    std::vector<std::unique_ptr<PFigure>> figures;
    std::vector<std::unique_ptr<PLight>> lights;
    bool stopDrawingAll = false;

    PObject *getActiveObject() const {
        return activeObject;
    }

    bool selectObjectByName(const std::string &targetName) {
        activeObject = nullptr;
        for (auto &figure: figures) {
            if (figure->name == targetName) {
                activeObject = figure.get();
                return true;
            }
        }

        for (auto &light: lights) {
            if (light->name == targetName) {
                activeObject = light.get();
                return true;
            }
        }

        return false;

    }

    void createLight(std::string name, Camera &cam, glm::vec3 pos,
                     glm::vec3 scale, float angle, Shader &shader,
                     Shader &lightShader, std::string type) {
        lights.push_back(
                std::make_unique<PLight>(name, cam, pos, scale, angle,
                                         shader, lightShader, type, lightCounter)
        );
        lightCounter++;
    }


    void createFigure(std::string name, Camera &cam, glm::vec3 pos,
                      glm::vec3 scale, float angle, Shader &shader,
                      std::string type,
                      const std::vector<std::string> &texturePaths) {
        figures.push_back(
                std::make_unique<PFigure>(name, cam, pos, scale, angle,
                                          shader, type, texturePaths));
    }


    void drawAll() {

        if (!stopDrawingAll) {
            for (auto &figure: figures) {
                figure->Draw();
            }

            for (auto &light: lights) {
                light->Draw();
            }
        }
    }


    void moveTo(vec3 newPos) {
        activeObject->position = newPos;

        cout << "move" << "\n";
    }

    void scaleTo(vec3 newScale) {
        activeObject->scale = newScale;

        cout << "scale" << "\n";
    }

    void rotateTo(float newAngle) {
        activeObject->angle = newAngle;

        cout << "rotate" << "\n";
    }

    void changeColor(vec3 newColor) {
        activeObject->color = newColor;


        cout << "changeColor" << "\n";
    }

    void deleteObj() {
        if (!activeObject) return;
        activeObject->isDrawing = false;


        for (auto it = figures.begin(); it != figures.end();) {
            if (it->get() == activeObject) {
                it = figures.erase(it);
                activeObject = nullptr;
                return;
            } else {
                ++it;
            }
        }

        for (auto it = lights.begin(); it != lights.end();) {
            if (it->get() == activeObject) {
                it = lights.erase(it);
                activeObject = nullptr;
                return;
            } else {
                ++it;
            }
        }
    }


    void deleteAllObjects() {
        for (auto &light: lights) {
            light->deleteObj();
        }

        for (auto &figure: figures) {
            figure->deleteObj();
        }

        lights.clear();
        figures.clear();
        activeObject = nullptr;
    }

};

#endif
