#include "include/Texture.h"

Texture::Texture(const char *image, const char* texType, GLenum slot) {

    std::cout << image << " " << ID;
    type = texType;
    int width, height , nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            width,
                            height,
                            0,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            data
                    );
        else if (nrChannels == 3)
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            width,
                            height,
                            0,
                            GL_RGB,
                            GL_UNSIGNED_BYTE,
                            data
                    );
        else if (nrChannels == 4)
            glTexImage2D
                    (
                            GL_TEXTURE_2D,
                            0,
                            GL_RGBA,
                            width,
                            height,
                            0,
                            GL_RGBA,
                            GL_UNSIGNED_BYTE,
                            data
                    );
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        glGenerateMipmap(GL_TEXTURE_2D);
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