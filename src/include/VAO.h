#ifndef VAO_H
#define VAO_H

#include "glad/glad.h"
#include "VBO.h"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO& vbo, GLuint layout, unsigned int location, unsigned long size1, const void* size2);
	void bindVAO();
	void unBindVAO();
	void deleteVAO();
};
#endif