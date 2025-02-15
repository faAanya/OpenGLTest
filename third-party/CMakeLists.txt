add_library(glad STATIC glad/glad/glad.c)
target_include_directories(glad PUBLIC glad)

add_subdirectory(glfw)
add_subdirectory(glm)

add_library(stb_image STATIC stb_image.c)
target_include_directories(stb_image PUBLIC stb)