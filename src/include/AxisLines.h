// AxisLines.h

#ifndef AXIS_LINES_H
#define AXIS_LINES_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h" // Твой класс шейдера

class AxisLines {
public:
    AxisLines();
    ~AxisLines();

    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint VAO, VBO;
    Shader shader;
};

#endif
