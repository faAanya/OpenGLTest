#include <glad/glad.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "include/shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "include/Camera.h"
#include "include/line_class.h"
#include "include/VAO.h"
#include "include/VBO.h"


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
float lastX = 400, lastY = 300;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool isFirstMouse = true;

const char *vertShaderPath = "resources\\shader.vert";
const char *fragShaderPath = "resources\\shader.frag";
const char *lightVertShaderPath = "resources\\lightningShader.vert";
const char *lightFragShaderPath = "resources\\lightningShader.frag";
const char *lightSourceVertShaderPath = "resources\\lightSource.vert";
const char *lightSourceFragShaderPath = "resources\\lightSource.frag";
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

    Line line1(vec3(0, 0, 0), vec3(1, 0, 0));
    line1.setColor(vec3(1, 0, 0));
    Line line2(vec3(0, 0, 0), vec3(0, 1, 0));
    line2.setColor(vec3(0, 1, 0));
    Line line3(vec3(0, 0, 0), vec3(0, 0, 1));
    line3.setColor(vec3(0, 0, 1));


//    Shader shaders(vertShaderPath, fragShaderPath);
    Shader lightShader(lightVertShaderPath, lightFragShaderPath);
    Shader lightSource(lightSourceVertShaderPath, lightSourceFragShaderPath);
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    VAO VAO1;
    VAO1.bindVAO();

    VBO VBO1(vertices, sizeof(vertices));


    VAO1.LinkVBO(VBO1, 0, 3, 6 * sizeof(float), (void *) 0);
    VAO1.LinkVBO(VBO1, 1, 2, 6 * sizeof(float), (void *) (3 * (sizeof(float))));
//    VAO1.unBindVAO();
//    VBO1.unBindVBO();

    VAO lightVAO;
    lightVAO.bindVAO();

    lightVAO.LinkVBO(VBO1, 0, 3, 6 * sizeof(float), (void *) 0);

    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    /*   unsigned int texture1;
       glGenTextures(1, &texture1);
       glBindTexture(GL_TEXTURE_2D, texture1);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

       int width, height, nrChannels;
       stbi_set_flip_vertically_on_load(true);
       unsigned char *data = stbi_load("resources\\popcat.jpg", &width, &height, &nrChannels,
                                       0);

       if (data) {
           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
           glGenerateMipmap(GL_TEXTURE_2D);
       } else {
           std::cout << "Failed to load texture" << std::endl;
       }
       stbi_image_free(data);

       unsigned int texture2;
       glGenTextures(1, &texture2);
       glBindTexture(GL_TEXTURE_2D, texture2);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

       data = stbi_load("resources\\cupcake1.jpg", &width, &height, &nrChannels, 0);
       if (data) {
           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
           glGenerateMipmap(GL_TEXTURE_2D);
       } else {
           std::cout << "Failed to load texture" << std::endl;
       }
       stbi_image_free(data);
   */
//    shaders.use();
//    shaders.setInt("texture1", 0);
//    shaders.setInt("texture2", 1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

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
        /* glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, texture1);
         glActiveTexture(GL_TEXTURE1);
         glBindTexture(GL_TEXTURE_2D, texture2);*/


        lightShader.use();
        lightShader.setVec3("viewPos", camera.Position);
        lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("lightColor", glm::vec3(color[0], color[1], color[2]));
        lightShader.setVec3("lightPos", lightPos);
        lightShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightShader.setFloat("material.shininess", 32);
        lightShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
        lightShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) WIDTH / (float) HEIGHT, 0.1f,
                                                100.0f);
        lightShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();

        lightShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        lightShader.setMat4("model", model);

        VAO1.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//        float angle = 0.0f;
//        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        lightSource.use();
        lightSource.setMat4("projection", projection);
        lightSource.setMat4("view", view);
        model = glm::mat4(1.0f);
        lightPos = vec3(sin(glfwGetTime()), 0.7f, cos(glfwGetTime()));
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightSource.setMat4("model", model);

        lightVAO.bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 36);


        line1.setMVP(projection * view);
        line2.setMVP(projection * view);
        line3.setMVP(projection * view);

        line1.draw();
        line2.draw();
        line3.draw();

        ImGui::Begin("Window");
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    VAO1.deleteVAO();
    VBO1.deleteVBO();

//    shaders.del();

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
