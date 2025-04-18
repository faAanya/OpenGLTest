#include "include/EBO.h"
#include <vector>
EBO::EBO(std::vector<GLuint>& indices) {
	glGenBuffers(1, &ID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), indices.data(), GL_STATIC_DRAW);
}
void EBO::bindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unBindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::deleteEBO() {
	glDeleteBuffers(1, &ID);
}