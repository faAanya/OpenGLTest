#include "include/ImguiManager.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

PImgui::PImgui(GLFWwindow *win) {
    this->window = win;
}

void PImgui::initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void PImgui::activeState() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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
}

void PImgui::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}