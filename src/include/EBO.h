#ifndef EBO_H
#define EBO_H
#include "glad/glad.h"
#include <vector>
class EBO {
public:
	unsigned int ID;
	EBO(std::vector<GLuint>& indices);

	void bindEBO();
	void unBindEBO();
	void deleteEBO();
};

#endif
