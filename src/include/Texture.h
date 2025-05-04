#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"

#include "Shader.h"

class Texture{
public:
    GLuint ID;
    const char* type;
    GLenum unit;

    Texture(const char* image, const char* texType, GLenum slot);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void UnBind();
    void Delete();

};

#endif
