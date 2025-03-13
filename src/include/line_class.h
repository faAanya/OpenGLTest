#ifndef Line_H
#define Line_H

#include "glad/glad.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <vector>
#include "VAO.h"
#include "shader.h"
#include "VBO.h"
using namespace std;
using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::lookAt;
using std::vector;

class Line
{
    int shaderProgram;
    VAO Vao;
    VBO Vbo = VBO(vertices);
    vector<Vertex> vertices;
    vec3 startPoint;
    vec3 endPoint;
    mat4 MVP = mat4(1.0);
    vec3 lineColor;
public:
    Line(vec3 start, vec3 end);
    int setMVP(mat4 mvp);
    int setColor(vec3 color);
    int draw();
    ~Line();
};

#endif