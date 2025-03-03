add_library(glad STATIC glad/glad/glad.c)
target_include_directories(glad PUBLIC glad)

add_library(imgui_lib STATIC imgui_lib.cpp)
target_include_directories(imgui_lib PUBLIC imgui)

add_library(stb_image STATIC stb_image.c)
target_include_directories(stb_image PUBLIC stb)

add_subdirectory(glfw)
add_subdirectory(glm)

add_subdirectory(assimp-master)
