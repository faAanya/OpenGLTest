#ifndef VBO_H
#define VBO_H
#include "glad/glad.h"
#include <vector>

using namespace std;
class VBO {
public:
	unsigned int ID;
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(vector<float>& vertices);

	void bindVBO();
	void unBindVBO();
	void deleteVBO();
};

#endif
