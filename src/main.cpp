#include <glad/glad.h>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "include/shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <include/Mesh.h>
#include "include/Camera.h"
#include "include/VBO.h"
#include "include/lua-maintainer.h"
#include "include/Texture.h"
#include "src/lua.hpp"
#include "include/verts.h"
#include "include/LightManager.h"
#include "include/FigureManager.h"

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

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

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

    Shader lightShader(lightVertShaderPath, lightFragShaderPath);
    Shader lightSource(lightSourceVertShaderPath, lightSourceFragShaderPath);


    Texture textures[] = {

            Texture("resources\\textures\\container2.png", "diffuse", GL_TEXTURE0),
            Texture("resources\\textures\\container2_specular.png", "specular", GL_TEXTURE1)

    };

    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh myMesh(verts::cube, tex);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    char inputText[256] = "";
    bool showMessage = false;

    PLight light1("light 1",
                  camera,
                  camera.Position,
                  vec3(-0.2f, -1.0f, -0.3f),
                  10,
                  lightShader,
                  lightSource,
                  "spot",
                  dirCount);

    PFigure obj("cube 1",
                camera,
                vec3(1.0f, 1.0f, 1.0f),
                vec3(1.0f, 2.0f, 1.0f),
                20,
                lightShader,
                "type",
                0);




    while (!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        light1.Draw();
        light1.meshDraw();
//        spot.meshDraw();
        obj.Draw(lightShader);
        ImGui::Begin("Window");

        ImGui::InputTextMultiline("Text", inputText, sizeof(inputText), ImVec2(250, 100));

        if (ImGui::Button("Submit")) {
            light1.moveTo(vec3(1.0f, 2.0f, -0.5f));
            showMessage = true;
        }


        if (showMessage) {
            ImGui::Text("You entered: %s", inputText);
            if (ImGui::Button("Hide message")) {
                showMessage = false;
            }
        }
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    lightShader.del();
    lightSource.del();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
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

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
        if (abs(xoffset) > 1.0f) {
            if (lastX < xpos)
                camera.ProcessMovement(deltaTime, LEFT);
            if (lastX > xpos)
                camera.ProcessMovement(deltaTime, RIGHT);
        }
        if (abs(yoffset) > 1.0f) {
            if (lastY < ypos)
                camera.ProcessMovement(deltaTime, UP);
            if (lastY > ypos)
                camera.ProcessMovement(deltaTime, DOWN);
        }
    }
    lastX = xpos;
    lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
        camera.ProcessMouseRotation(xoffset, yoffset);
    }

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}