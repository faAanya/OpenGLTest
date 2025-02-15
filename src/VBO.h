#ifndef VBO_H
#define VBO_H
#include <glad/glad.h>

class VBO {
public:
	unsigned int ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void bindVBO();
	void unBindVBO();
	void deleteVBO();
};

#endif
