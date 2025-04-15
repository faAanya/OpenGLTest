#ifndef TESTBUILD_IMGUIMANAGER_H
#define TESTBUILD_IMGUIMANAGER_H
#include "GLFW/glfw3.h"


class PImgui {
private:
    GLFWwindow* window;
    char inputText[256] = "";
    bool showMessage = false;
public:

    PImgui(GLFWwindow* win);
   void initialize();
   void activeState();
   void destroy();

};


#endif //TESTBUILD_IMGUIMANAGER_H
