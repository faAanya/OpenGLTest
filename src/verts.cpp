#include "include/verts.h"

namespace verts {

    Vertex cube[36] = {
            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},

            Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

            Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

            Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
    };

    Vertex pyramid[] = {

            {{-0.5f, 0.0f, -0.5f}, {0.0f,    -1.0f,  0.0f},    {0.0f, 0.0f}}, // A
            {{0.5f,  0.0f, -0.5f}, {0.0f,    -1.0f,  0.0f},    {1.0f, 0.0f}}, // B
            {{0.5f,  0.0f, 0.5f},  {0.0f,    -1.0f,  0.0f},    {1.0f, 1.0f}}, // C

            {{-0.5f, 0.0f, -0.5f}, {0.0f,    -1.0f,  0.0f},    {0.0f, 0.0f}}, // A
            {{0.5f,  0.0f, 0.5f},  {0.0f,    -1.0f,  0.0f},    {1.0f, 1.0f}}, // C
            {{-0.5f, 0.0f, 0.5f},  {0.0f,    -1.0f,  0.0f},    {0.0f, 1.0f}}, // D


            {{-0.5f, 0.0f, 0.5f},  {0.0f,    0.707f, 0.707f},  {0.0f, 0.0f}}, // D
            {{0.5f,  0.0f, 0.5f},  {0.0f,    0.707f, 0.707f},  {1.0f, 0.0f}}, // C
            {{0.0f,  1.0f, 0.0f},  {0.0f,    0.707f, 0.707f},  {0.5f, 1.0f}}, // Top


            {{0.5f,  0.0f, 0.5f},  {0.707f,  0.707f, 0.0f},    {0.0f, 0.0f}}, // C
            {{0.5f,  0.0f, -0.5f}, {0.707f,  0.707f, 0.0f},    {1.0f, 0.0f}}, // B
            {{0.0f,  1.0f, 0.0f},  {0.707f,  0.707f, 0.0f},    {0.5f, 1.0f}}, // Top


            {{0.5f,  0.0f, -0.5f}, {0.0f,    0.707f, -0.707f}, {1.0f, 0.0f}}, // B
            {{-0.5f, 0.0f, -0.5f}, {0.0f,    0.707f, -0.707f}, {0.0f, 0.0f}}, // A
            {{0.0f,  1.0f, 0.0f},  {0.0f,    0.707f, -0.707f}, {0.5f, 1.0f}}, // Top


            {{-0.5f, 0.0f, -0.5f}, {-0.707f, 0.707f, 0.0f},    {1.0f, 0.0f}}, // A
            {{-0.5f, 0.0f, 0.5f},  {-0.707f, 0.707f, 0.0f},    {0.0f, 0.0f}}, // D
            {{0.0f,  1.0f, 0.0f},  {-0.707f, 0.707f, 0.0f},    {0.5f, 1.0f}}, // Top
    };

    Vertex plane[6] = {
            // Первый треугольник
            {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // A: bottom left
            {{0.5f,  0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // B: bottom right
            {{0.5f,  0.0f, 0.5f},  {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // C: top right

            // Второй треугольник
            {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // A: bottom left
            {{0.5f,  0.0f, 0.5f},  {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // C: top right
            {{-0.5f, 0.0f, 0.5f},  {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // D: top left
    };

Vertex *sphere(float radius, unsigned int stacks, unsigned int slices, size_t &outVertexCount) {
    std::vector<Vertex> vertices;

    for (unsigned int i = 0; i < stacks; ++i) {
        float phi1 = glm::pi<float>() * static_cast<float>(i) / stacks;
        float phi2 = glm::pi<float>() * static_cast<float>(i + 1) / stacks;

        for (unsigned int j = 0; j <= slices; ++j) {
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / slices;

            for (int k = 0; k < 2; ++k) {
                float phi = (k == 0) ? phi1 : phi2;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                Vertex vertex;
                vertex.Position = glm::vec3(
                        radius * sinPhi * cos(theta),
                        radius * cosPhi,
                        radius * sinPhi * sin(theta)
                );
                vertex.Normal = glm::normalize(vertex.Position);
                vertex.texUV = glm::vec2(
                        static_cast<float>(j) / slices,
                        1.0f - static_cast<float>(i + k) / stacks
                );

                vertices.push_back(vertex);
            }
        }

        if (i != stacks - 1) {
            vertices.push_back(vertices.back());
            vertices.push_back(vertices[vertices.size() - (2 * (slices + 1) + 1)]);
        }
    }

    outVertexCount = vertices.size();
    Vertex *result = new Vertex[outVertexCount];
    std::copy(vertices.begin(), vertices.end(), result);
    return result;
}

}