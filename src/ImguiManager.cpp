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

    drawTopMenu();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void PImgui::drawTopMenu() {

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Main"))
        {
            ImGui::EndMenu();
        }

        ImGui::SetNextWindowSize(textWindowSize, ImGuiCond_FirstUseEver);

        // Автоматическое позиционирование
        if (currentPinState != PIN_NONE)
        {
            ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
            ImVec2 targetPos = ImVec2(0, 0);

            switch(currentPinState) {
                case PIN_LEFT:
                    targetPos = ImVec2(0, ImGui::GetFrameHeight());
                    break;
                case PIN_RIGHT:
                    targetPos = ImVec2(
                            viewportSize.x - textWindowSize.x,
                            ImGui::GetFrameHeight()
                    );
                    break;
                case PIN_BOTTOM:
                    targetPos = ImVec2(
                            0,
                            viewportSize.y - textWindowSize.y
                    );
                    break;
                default: break;
            }

            ImGui::SetNextWindowPos(targetPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(textWindowSize, ImGuiCond_Always);
        }

        ImGuiWindowFlags flags = currentPinState != PIN_NONE ?
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize :
                                 ImGuiWindowFlags_None;

        if (ImGui::Begin("Text Input", nullptr, flags))
        {

            if (ImGui::Button("Pin to Left"))
                currentPinState = PIN_LEFT;

            ImGui::SameLine();
            if (ImGui::Button("Pin to Right"))
                currentPinState = PIN_RIGHT;

            ImGui::SameLine();
            if (ImGui::Button("Pin to Bottom"))
                currentPinState = PIN_BOTTOM;

            ImGui::SameLine();
            if (ImGui::Button("Unpin"))
                currentPinState = PIN_NONE;

            ImGui::InputTextMultiline("##input", inputText,
                                      IM_ARRAYSIZE(inputText), ImVec2(-1, 100));

            if (ImGui::Button("Submit", ImVec2(-1, 0)))
                showMessage = true;

            if (showMessage) {
                ImGui::Separator();
                ImGui::Text("You entered: %s", inputText);
                if (ImGui::Button("Hide message"))
                    showMessage = false;
            }

            textWindowSize = ImGui::GetWindowSize();
            ImGui::End();
        }

        if (ImGui::BeginMenu("Create"))
        {

            if (ImGui::BeginMenu("Primitive"))
            {
                ImGui::MenuItem("Cube");
                ImGui::MenuItem("Sphere");
                ImGui::MenuItem("Cylinder");
                ImGui::MenuItem("Pyramid");
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Light"))
            {
                ImGui::MenuItem("Directional");
                ImGui::MenuItem("Spot");
                ImGui::MenuItem("Point");
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("About"))
        {
            show_about_window = true;
        }

        ImGui::EndMainMenuBar();
    }

    if (show_about_window)
    {
        ImGui::Begin("About", &show_about_window, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("3D Editor Application");
        ImGui::Separator();
        ImGui::Text("Version: 1.0.0");
        ImGui::Text("Basic scene manipulation tool");
        ImGui::Separator();

        ImGui::End();
    }
}

void PImgui::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}