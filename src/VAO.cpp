#include "include/VAO.h"

VAO::VAO() {
	glGenVertexArrays(1,&ID);
}
void VAO::LinkVBO(VBO& vbo, GLuint layout, unsigned int location, unsigned long size1, const void* size2) {
	vbo.bindVBO();
	glVertexAttribPointer(layout, location, GL_FLOAT, GL_FALSE, size1, size2);
	glEnableVertexAttribArray(layout);
	
	vbo.unBindVBO();
}

void VAO::bindVAO() {
	glBindVertexArray(ID);
}
void VAO::unBindVAO() {
	glBindVertexArray(0);
}
void VAO::deleteVAO() {
	glDeleteVertexArrays(1, &ID);
}