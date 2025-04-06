#ifndef TESTBUILD_OBJECT_H
#define TESTBUILD_OBJECT_H
#include "string"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace glm;
class PObject{
public:
    string name;
    vec3 position;

//    Object();
    PObject(string n, vec3 pos);
};

#endif //TESTBUILD_OBJECT_H
