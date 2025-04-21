#ifndef TESTBUILD_PIMGUI_H
#define TESTBUILD_PIMGUI_H
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

class PImgui {
private:
    GLFWwindow* window;
    bool show_about_window = false;

    char inputText[1024] = "";
    bool showMessage = false;
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
    void CreatePrimitive_Cube();
    void CreatePrimitive_Sphere();
    void CreatePrimitive_Cylinder();
    void CreatePrimitive_Pyramid();

    void CreateLight_Directional();
    void CreateLight_Spot();
    void CreateLight_Point();
public:

    PImgui(GLFWwindow* win);
   void initialize();
   void activeState();
   void drawTopMenu();
   void destroy();

};


#endif //TESTBUILD_PIMGUI_H
