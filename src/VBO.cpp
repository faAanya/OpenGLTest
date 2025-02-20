#include "VBO.h"

VBO::VBO(GLfloat* vertices,  GLsizeiptr size) {
	glGenBuffers(1, &ID);

	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER,size, vertices, GL_STATIC_DRAW);
}
VBO::VBO(vector<float>& vertices) {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
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