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
#include <filesystem>
#include "include/Camera.h"
#include "include/line_class.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/lua-maintainer.h"
#include "include/Texture.h"
#include "src/lua.hpp"
#include "include/verts.h"
#include "include/LightManager.h"

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

glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
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

    vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));

    vector<Vertex> vert(verts::cube, verts::cube + sizeof(verts::cube) / sizeof(Vertex));
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh myMesh(vert, tex);
    Mesh light(vert, tex);



    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    char inputText[256] = "";
    bool showMessage = false;

    PLight light1("light 1", vec3(-0.2f, -1.0f, -0.3f), lightShader, "directional", 0);
    PLight point("light 2", pointLightPositions[0], lightShader, "point", 0);
    PLight spot("light 3", vec3(1, 1, 1), lightShader, "spot", 0);

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

        lightShader.use();
        lightShader.setVec3("viewPos", camera.Position);
        lightShader.setFloat("material.shininess", 32.0f);

        light1.Draw(lightShader, camera);
//        point.Draw(camera);
//        spot.Draw(camera);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) WIDTH / (float) HEIGHT, 0.1f,
                                                100.0f);
        lightShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();

        lightShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        lightShader.setMat4("model", model);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightShader.setMat4("model", model);

            light.Draw(lightShader, camera);
        }


        lightSource.use();
        lightSource.setMat4("projection", projection);
        lightSource.setMat4("view", view);


//        for (unsigned int i = 0; i < 4; i++) {
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, pointLightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//            lightSource.setMat4("model", model);
//        }
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[0]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        lightSource.setMat4("model", model);
        light.Draw(lightSource, camera);


        ImGui::Begin("Window");

        ImGui::InputTextMultiline("Text", inputText, sizeof(inputText), ImVec2(250, 100));

        if (ImGui::Button("Submit")) {
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
//    glfwDestroyWindow(window);
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