#ifndef TESTBUILD_PIMGUI_H
#define TESTBUILD_PIMGUI_H

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "ObjectManager.h"
#include "PLua.h"

class PImgui {
private:
    GLFWwindow *window;
    ObjectManager *manager;
    PLua* lua;
    bool showAboutWindow = false;


    char inputText[1024] = "";
    bool isChangingScene = false;
    ImGuiWindowFlags textWindowFlags = ImGuiWindowFlags_None;
    bool textWindowPinned = true;
    ImVec2 textWindowSize = ImVec2(500, 200);

    enum WindowPinState {
        PIN_NONE,
        PIN_LEFT,
        PIN_RIGHT,
        PIN_BOTTOM
    };

    WindowPinState currentPinState = PIN_NONE;

    void createFigure(const std::string& command);

    void createLight();

public:
    bool isInputActive;

    PImgui(GLFWwindow *win, ObjectManager* m, PLua* l);

    void initialize();

    void activeState();

    void drawTopMenu();

    void drawHierarchy();
    void checkInput();

    void destroy();

};


#endif //TESTBUILD_PIMGUI_H
