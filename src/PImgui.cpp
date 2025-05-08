#include "include/PImgui.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "include/ObjectManager.h"
#include "include/PLua.h"


PImgui::PImgui(GLFWwindow *win, ObjectManager *m, PLua *l) {
    this->window = win;
    this->manager = m;
    this->lua = l;
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
    drawHierarchy();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void PImgui::drawTopMenu() {

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Main")) {
            ImGui::EndMenu();
        }

        ImGui::SetNextWindowSize(textWindowSize, ImGuiCond_FirstUseEver);

        if (currentPinState != PIN_NONE) {
            ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
            ImVec2 targetPos = ImVec2(0, 0);

            switch (currentPinState) {
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
                default:
                    break;
            }

            ImGui::SetNextWindowPos(targetPos, ImGuiCond_Always);
            ImGui::SetNextWindowSize(textWindowSize, ImGuiCond_Always);
        }

        ImGuiWindowFlags flags = currentPinState != PIN_NONE ?
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize :
                                 ImGuiWindowFlags_None;

        if (ImGui::Begin("Text Input", nullptr, flags)) {

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
            checkInput();
            if (ImGui::Button("Submit", ImVec2(-1, 0))) {
                isChangingScene = true;
            }

            if (isChangingScene) {
                ImGui::Separator();
                ImGui::Text("You entered: %s", inputText);
                lua->loadScriptFromTextBox(inputText);
                isChangingScene = false;
                inputText[0] = '\0';
            }

            textWindowSize = ImGui::GetWindowSize();
            ImGui::End();
        }

        if (ImGui::BeginMenu("Create")) {

            if (ImGui::BeginMenu("Primitive")) {
                ImGui::MenuItem("Cube");
                ImGui::MenuItem("Sphere");
                ImGui::MenuItem("Cylinder");
                ImGui::MenuItem("Pyramid");
                ImGui::MenuItem("Plane");
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Light")) {
                ImGui::MenuItem("Directional");
                ImGui::MenuItem("Spot");
                ImGui::MenuItem("Point");
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("About")) {
            showAboutWindow = true;
        }

        ImGui::EndMainMenuBar();
    }

    if (showAboutWindow) {
        ImGui::Begin("Library", &showAboutWindow, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::CollapsingHeader("Object Creation", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::BulletText("figure(name, pos_x, pos_y, pos_z, scale_x, scale_y, scale_z, angle, type, textures_table)");
            ImGui::Indent();
            ImGui::Text("Creates a new 3D figure with:");
            ImGui::BulletText("name: string identifier");
            ImGui::BulletText("position: x,y,z coordinates");
            ImGui::BulletText("scale: x,y,z dimensions");
            ImGui::BulletText("angle: rotation angle");
            ImGui::BulletText("type: figure type (string)");
            ImGui::BulletText("textures: array of texture paths");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("light(name, pos_x, pos_y, pos_z, scale_x, scale_y, scale_z, angle, type)");
            ImGui::Indent();
            ImGui::Text("Creates a new light source with:");
            ImGui::BulletText("name: string identifier");
            ImGui::BulletText("position: x,y,z coordinates");
            ImGui::BulletText("scale: x,y,z dimensions");
            ImGui::BulletText("angle: rotation angle");
            ImGui::BulletText("type: light type (\"spot\", \"point\" or \"directional\")");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Object Selection")) {
            ImGui::BulletText("pick_object(name)");
            ImGui::Indent();
            ImGui::Text("Selects an object by its name for subsequent operations");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Transformations")) {
            ImGui::BulletText("move_to(x, y, z)");
            ImGui::Indent();
            ImGui::Text("Moves currently selected object to position (x,y,z)");
            ImGui::Unindent();

            ImGui::BulletText("move_to(name, x, y, z)");
            ImGui::Indent();
            ImGui::Text("Moves specified object to position (x,y,z)");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("scale_to(x, y, z)");
            ImGui::Indent();
            ImGui::Text("Scales currently selected object");
            ImGui::Unindent();

            ImGui::BulletText("scale_to(name, x, y, z)");
            ImGui::Indent();
            ImGui::Text("Scales specified object");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("rotate_to(angle)");
            ImGui::Indent();
            ImGui::Text("Rotates currently selected object by angle");
            ImGui::Unindent();

            ImGui::BulletText("rotate_to(name, angle)");
            ImGui::Indent();
            ImGui::Text("Rotates specified object by angle");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Light Properties")) {
            ImGui::BulletText("set_direction(x, y, z)");
            ImGui::Indent();
            ImGui::Text("Sets light direction vector");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("set_ambient(r, g, b)");
            ImGui::Indent();
            ImGui::Text("Sets ambient light color (RGB 0-1)");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("set_diffuse(r, g, b)");
            ImGui::Indent();
            ImGui::Text("Sets diffuse light color (RGB 0-1)");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("set_specular(r, g, b)");
            ImGui::Indent();
            ImGui::Text("Sets specular light color (RGB 0-1)");
            ImGui::Unindent();

            ImGui::Spacing();
            ImGui::BulletText("set_radius(cutoff)");
            ImGui::Indent();
            ImGui::Text("Sets spotlight inner radius (cutoff angle)");
            ImGui::Unindent();

            ImGui::BulletText("set_radius_outer(outer_cutoff)");
            ImGui::Indent();
            ImGui::Text("Sets spotlight outer radius");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Object Appearance")) {
            ImGui::BulletText("set_color(r, g, b)");
            ImGui::Indent();
            ImGui::Text("Changes color of currently selected object (RGB 0-1)");
            ImGui::Unindent();

            ImGui::BulletText("set_color(name, r, g, b)");
            ImGui::Indent();
            ImGui::Text("Changes color of specified object");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Object Management")) {
            ImGui::BulletText("delete_object()");
            ImGui::Indent();
            ImGui::Text("Deletes currently selected object");
            ImGui::Unindent();

            ImGui::BulletText("delete_all()");
            ImGui::Indent();
            ImGui::Text("Deletes all objects in the scene");
            ImGui::Unindent();
        }

        ImGui::End();
    }


}

void PImgui::drawHierarchy() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(
            viewportSize.x - textWindowSize.x,
            ImGui::GetFrameHeight()), ImGuiCond_Always);

    ImGui::Begin("Hierarchy", nullptr, flags);
    if(manager->getActiveObject())
        ImGui::Text("%s %s", "Active object:", manager->getActiveObject()->name.c_str());

    if (ImGui::BeginTable("Hierarchy", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Position");
        ImGui::TableHeadersRow();

        if (manager) {
            for (auto &figure: manager->figures) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", figure->name.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("(%.2f, %.2f, %.2f)",
                            figure->position.x,
                            figure->position.y,
                            figure->position.z);
            }
            for (auto &figure: manager->lights) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", figure->name.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("(%.2f, %.2f, %.2f)",
                            figure->position.x,
                            figure->position.y,
                            figure->position.z);
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void PImgui::checkInput() {
    isInputActive = ImGui::IsItemActive();
}

void PImgui::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

