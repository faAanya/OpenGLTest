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

    if(isActiveUI){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawTopMenu();
        drawHierarchy();
        drawColorPicker();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void PImgui::drawTopMenu() {

    if (ImGui::BeginMainMenuBar()) {
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
                lua->loadScriptFromTextBox(inputText);
                isChangingScene = false;
                inputText[0] = '\0';
            }

            textWindowSize = ImGui::GetWindowSize();
            ImGui::End();
        }

        if (ImGui::BeginMenu("Pick")) {
            for (auto& figure : manager->figures) {
                if (ImGui::MenuItem(figure->name.c_str())) {
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "pick('%s')\n", figure->name.c_str());
                    strcat(inputText, buffer);
                }
            }

            for (auto& light : manager->lights) {
                if (ImGui::MenuItem(light->name.c_str())) {
                    char buffer[256];
                    snprintf(buffer, sizeof(buffer), "pick('%s')\n", light->name.c_str());
                    strcat(inputText, buffer);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Create")) {
            static int cubeCount = 1;
            static int sphereCount = 1;
            static int cylinderCount = 1;
            static int pyramidCount = 1;
            static int planeCount = 1;
            static int directionalLightCount = 1;
            static int spotLightCount = 1;
            static int pointLightCount = 1;

            if (ImGui::BeginMenu("Primitive")) {
                char buffer[256];

                if (ImGui::MenuItem("Cube")) {
                    snprintf(buffer, sizeof(buffer),
                             "figure('cube_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'cube', {})\n",
                             cubeCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Sphere")) {
                    snprintf(buffer, sizeof(buffer),
                             "figure('sphere_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'sphere', {})\n",
                             sphereCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Cylinder")) {
                    snprintf(buffer, sizeof(buffer),
                             "figure('cylinder_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'cylinder', {})\n",
                             cylinderCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Pyramid")) {
                    snprintf(buffer, sizeof(buffer),
                             "figure('pyramid_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'pyramid', {})\n",
                             pyramidCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Plane")) {
                    snprintf(buffer, sizeof(buffer),
                             "figure('plane_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'plane', {})\n",
                             planeCount++);
                    strcat(inputText, buffer);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Light")) {
                char buffer[256];

                if (ImGui::MenuItem("Directional")) {
                    snprintf(buffer, sizeof(buffer),
                             "light('directional_light_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'directional')\n",
                             directionalLightCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Spot")) {
                    snprintf(buffer, sizeof(buffer),
                             "light('spot_light_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'spot')\n",
                             spotLightCount++);
                    strcat(inputText, buffer);
                }

                if (ImGui::MenuItem("Point")) {
                    snprintf(buffer, sizeof(buffer),
                             "light('point_light_%d', 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 'point')\n",
                             pointLightCount++);
                    strcat(inputText, buffer);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Modify")) {

            if (ImGui::BeginMenu("Transformation")) {
                if (ImGui::MenuItem("Object Position")) {
                    strcat(inputText, "move(x, y, z)\n");
                }
                if (ImGui::MenuItem("Object Scale")) {
                    strcat(inputText, "scale(x, y, z)\n");
                }
                if (ImGui::MenuItem("Object Rotation")) {
                    strcat(inputText, "rotate(angle)\n");
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Properties")) {
                if (ImGui::MenuItem("Object Color")) {
                    strcat(inputText, "color(r, g, b)\n");
                }
                if (ImGui::MenuItem("Object Texture")) {
                    strcat(inputText, "add_texture(name, path, textureType)\n");
                }
                if (ImGui::MenuItem("Light Direction")) {
                    strcat(inputText, "direction(x, y, z)\n");
                }
                if (ImGui::MenuItem("Light Ambient")) {
                    strcat(inputText, "ambient(r, g, b)\n");
                }
                if (ImGui::MenuItem("Light Diffuse")) {
                    strcat(inputText, "diffuse(r, g, b)\n");
                }
                if (ImGui::MenuItem("Light Specular")) {
                    strcat(inputText, "specular(r, g, b)\n");
                }
                if (ImGui::MenuItem("Light Cutoff")) {
                    strcat(inputText, "radius(cutoff)\n");
                }
                if (ImGui::MenuItem("Light OuterCutoff")) {
                    strcat(inputText, "radius_outer(outer_cutoff)\n");
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) {
            ImGui::Begin("Library", &showAboutWindow, ImGuiWindowFlags_AlwaysAutoResize);

            if (ImGui::CollapsingHeader("Hotkeys", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::BulletText("H: Hide UI");
                ImGui::BulletText("J: Show UI");
                ImGui::BulletText("R: Save screenshot (render.png)");
                ImGui::BulletText("ALT + Mouse: Rotate camera");
                ImGui::BulletText("WASD: Move camera");
                ImGui::BulletText("Mouse Scroll: Zoom in/out");
            }

            if (ImGui::CollapsingHeader("Object Creation", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::BulletText(
                        "figure(name, pos_x, pos_y, pos_z, scale_x, scale_y, scale_z, angle, type, textures_table)");
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
                ImGui::BulletText("pick(name)");
                ImGui::Indent();
                ImGui::Text("Selects an object by its name for subsequent operations");
                ImGui::Unindent();
            }

            if (ImGui::CollapsingHeader("Transformations")) {
                ImGui::BulletText("move(x, y, z)");
                ImGui::Indent();
                ImGui::Text("Moves currently selected object to position (x,y,z)");
                ImGui::Unindent();

                ImGui::BulletText("move(name, x, y, z)");
                ImGui::Indent();
                ImGui::Text("Moves specified object to position (x,y,z)");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("scale(x, y, z)");
                ImGui::Indent();
                ImGui::Text("Scales currently selected object");
                ImGui::Unindent();

                ImGui::BulletText("scale(name, x, y, z)");
                ImGui::Indent();
                ImGui::Text("Scales specified object");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("rotate(angle)");
                ImGui::Indent();
                ImGui::Text("Rotates currently selected object by angle");
                ImGui::Unindent();

                ImGui::BulletText("rotate(name, angle)");
                ImGui::Indent();
                ImGui::Text("Rotates specified object by angle");
                ImGui::Unindent();
            }

            if (ImGui::CollapsingHeader("Light Properties")) {
                ImGui::BulletText("direction(x, y, z)");
                ImGui::Indent();
                ImGui::Text("Sets light direction vector");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("ambient(r, g, b)");
                ImGui::Indent();
                ImGui::Text("Sets ambient light color (RGB 0-1)");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("diffuse(r, g, b)");
                ImGui::Indent();
                ImGui::Text("Sets diffuse light color (RGB 0-1)");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("specular(r, g, b)");
                ImGui::Indent();
                ImGui::Text("Sets specular light color (RGB 0-1)");
                ImGui::Unindent();

                ImGui::Spacing();
                ImGui::BulletText("radius(cutoff)");
                ImGui::Indent();
                ImGui::Text("Sets spotlight inner radius (cutoff angle)");
                ImGui::Unindent();

                ImGui::BulletText("radius_outer(outer_cutoff)");
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

                ImGui::BulletText("add_texture(path)");
                ImGui::Indent();
                ImGui::Text("Adds a new texture from file path to the selected object");
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
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}
void PImgui::drawHierarchy() {

    ImVec2 viewportSize = ImGui::GetMainViewport()->Size;

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;


    ImGui::SetNextWindowPos(ImVec2(
            viewportSize.x - hierarchyWidth,
            ImGui::GetFrameHeight()
    ), ImGuiCond_Always);


    ImGui::SetNextWindowSize(ImVec2(
            hierarchyWidth,
            viewportSize.y - ImGui::GetFrameHeight()
    ), ImGuiCond_Always);


    ImGui::Begin("Hierarchy", nullptr, flags);


    if (manager->getActiveObject())
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
void PImgui::drawColorPicker() {

    ImGui::Begin("Color Picker", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::ColorPicker3("Object Color", (float*)&objectColor)) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "color(%.2f, %.2f, %.2f)\n",
                 objectColor.x, objectColor.y, objectColor.z);
        strcat(inputText, buffer);
        isChangingScene = true;
    }

    ImGui::End();
}
void PImgui::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

