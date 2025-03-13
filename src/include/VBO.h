#ifndef VBO_H
#define VBO_H
#include "glad/glad.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 texUV;
};


class VBO {
public:
	unsigned int ID;
	VBO(std::vector<Vertex>& vertices);

	void bindVBO();
	void unBindVBO();
	void deleteVBO();
};

#endif
