#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"

#include "shader.h"

class Texture{
public:
    GLuint ID;
    const char* type;
    GLuint unit;

    Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void UnBind();
    void Delete();

};

#endif
