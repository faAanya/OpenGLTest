#include <glad/glad.h>
#include <iostream>
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "include/Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "include/Camera.h"
#include "include/PLua.h"
#include "src/lua.hpp"
#include "include/PImgui.h"
#include "include/AxisLines.h"
#include "include/ObjectManager.h"
#include "include/GlobalVars.h"
#include "stb_image_write.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;
float lastX = 640, lastY = 360;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool isFirstMouse = true;

const char *lightVertShaderPath = "resources\\shaders\\lightningShader.vert";
const char *lightFragShaderPath = "resources\\shaders\\lightningShader.frag";
const char *lightSourceVertShaderPath = "resources\\shaders\\lightSource.vert";
const char *lightSourceFragShaderPath = "resources\\shaders\\lightSource.frag";


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void setBackGroundColor(glm::vec3 color);

void saveFrameToPng(const char *filename, int width, int height);

bool once = true;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Window", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    AxisLines axes;
    ObjectManager manager;
    Shader objectShader(lightVertShaderPath, lightFragShaderPath);
    Shader lightShader(lightSourceVertShaderPath, lightSourceFragShaderPath);
    GlobalVars globals(camera, objectShader, lightShader);

    PLua lua(globals, manager);
    lua.registerFunctions();
    PImgui imgui(window, &manager, &lua);
    imgui.initialize();

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (!imgui.isInputActive)
            processInput(window);

        setBackGroundColor(vec3(1.0f, 1.0f, 1.0f));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) WIDTH / (float) HEIGHT, 0.1f,
                                                100.0f);

        manager.drawAll();

        if(imgui.isActiveUI)
            axes.Draw(camera.GetViewMatrix(), projection);
        if(!imgui.isInputActive){
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && once) {
                saveFrameToPng("render.png", WIDTH, HEIGHT);
            }
            if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && imgui.isActiveUI) {
                imgui.isActiveUI = false;
            }
            if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && !imgui.isActiveUI) {
                imgui.isActiveUI = true;
            }

        }

        imgui.activeState();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    imgui.destroy();

    objectShader.del();
    lightShader.del();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (isFirstMouse) {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void saveFrameToPng(const char *filename, int width, int height) {
    unsigned char *pixels = new unsigned char[3 * width * height];

    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    for (int j = 0; j < height / 2; ++j) {
        for (int i = 0; i < width * 3; ++i) {
            std::swap(pixels[j * width * 3 + i], pixels[(height - 1 - j) * width * 3 + i]);
        }
    }

    stbi_write_png(filename, width, height, 3, pixels, width * 3);

    delete[] pixels;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void setBackGroundColor(glm::vec3 color) {
    glClearColor(color.x, color.y, color.z, 1.0f);
}