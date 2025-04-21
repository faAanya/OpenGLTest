// AxisLines.cpp

#include "include/AxisLines.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
};

AxisLines::AxisLines()
        : shader("resources\\shaders\\axis.vert", "resources\\shaders\\axis.frag")
{
    Vertex axisVertices[] = {
            // X (красная)
            {{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
            // Y (зелёная)
            {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
            // Z (синяя)
            {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

AxisLines::~AxisLines() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void AxisLines::Draw(const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}
