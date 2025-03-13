#include "include/VBO.h"

VBO::VBO(std::vector<Vertex>& vertices) {
	glGenBuffers(1, &ID);

	glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unBindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::deleteVBO() {
	glDeleteBuffers(1, &ID);
}