#include <glad/glad.h>
#include <iostream>
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "include/shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include "include/Camera.h"
#include "include/VBO.h"
#include "include/lua-maintainer.h"
#include "include/Texture.h"
#include "src/lua.hpp"
#include "include/LightManager.h"
#include "include/FigureManager.h"
#include "include/ImguiManager.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;
float lastX = 640, lastY = 360;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool isFirstMouse = true;

unsigned int pointCount;
unsigned int spotCount;
unsigned int dirCount = 0;

const char *lightVertShaderPath = "resources\\shaders\\lightningShader.vert";
const char *lightFragShaderPath = "resources\\shaders\\lightningShader.frag";
const char *lightSourceVertShaderPath = "resources\\shaders\\lightSource.vert";
const char *lightSourceFragShaderPath = "resources\\shaders\\lightSource.frag";


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

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

    Shader objectShader(lightVertShaderPath, lightFragShaderPath);
    Shader lightShader(lightSourceVertShaderPath, lightSourceFragShaderPath);


    Texture textures[] = {

            Texture("resources\\textures\\container2.png", "diffuse", GL_TEXTURE0),
            Texture("resources\\textures\\container2_specular.png", "specular", GL_TEXTURE1)
    };
    Texture textures1[] = {

            Texture("resources\\textures\\cupcake.jpg", "diffuse", GL_TEXTURE0),
//            Texture("resources\\textures\\cupcake.jpg", "specular", GL_TEXTURE1)
    };
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    std::vector<Texture> tex1(textures1, textures1 + sizeof(textures1) / sizeof(Texture));


    PImgui imgui(window);
    imgui.initialize();

    PLight light1("light 1",
                  camera,
                  vec3(0.0f, 1.0f, 1.0f),
                  vec3(0.8f, 1.0f, 1.0f),
                  10,
                  objectShader,
                  lightShader,
                  "directional",
                  dirCount);

    PFigure obj("cube 1",
                camera,
                vec3(1.0f, 1.0f, 1.0f),
                vec3(1.0f, 2.0f, 1.0f),
                20,
                objectShader,
                "type",
                0,
                tex);
    PFigure obj1("cube 1",
                 camera,
                 vec3(2.0f, 2.0f, 2.0f),
                 vec3(1.0f, 2.0f, 1.0f),
                 20,
                 objectShader,
                 "type",
                 0,
                 tex1);


    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        light1.Draw();
        light1.meshDraw();
        obj1.Draw(objectShader);
        obj.Draw(objectShader);

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
    if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
    camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}