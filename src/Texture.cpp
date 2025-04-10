#include "include/Texture.h"

Texture::Texture(const char *image, const char* texType, GLenum slot, GLenum pixelType) {

    std::cout << image << " " << ID;
    type = texType;
    int width, height , nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);

    glGenTextures(1, &ID);
    glActiveTexture(slot);

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
    }
}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit) {
    shader.use();
    shader.setInt(uniform, unit);
}

void Texture::Bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}