file (GLOB_RECURSE SOURCES "*.cpp")
add_executable(OpenGLTest ${SOURCES}
        include/Mesh.h
        include/Model.h
        include/Texture.h
        Texture.cpp
        Mesh.cpp
        lua-maintainer.cpp
        lua-maintainer.h
)

target_include_directories(OpenGLTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
        OpenGLTest PUBLIC
        glad
        glfw
        glm::glm
        stb_image
        imgui_lib
        assimp::assimp
        lua
)