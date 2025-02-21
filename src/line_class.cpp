#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <vector>
#include "line_class.h"
#include "VBO.h"

using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::lookAt;
using std::vector;

Line::Line(vec3 start, vec3 end) {

    startPoint = start;
    endPoint = end;
    lineColor = vec3(1, 1, 1);
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "uniform mat4 MVP;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec3 color;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(color, 1.0f);\n"
                                       "}\n\0";

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vertices = {
            start.x, start.y, start.z,
            end.x, end.y, end.z,
    };
    
    Vao.bindVAO();
    Vbo = VBO( vertices);


    Vao.LinkVBO(Vbo,0, 3, 3 * sizeof(float), (void *) 0);

    Vao.bindVAO();
}

int Line::setMVP(mat4 mvp) {
    MVP = mvp;
    return 1;
}

int Line::setColor(vec3 color) {
    lineColor = color;
    return 1;
}

int Line::draw() {
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);

    Vao.bindVAO();
    glDrawArrays(GL_LINES, 0, 2);
    return 1;
}

Line::~Line() {
    Vao.deleteVAO();
    Vbo.deleteVBO();
    glDeleteProgram(shaderProgram);
}