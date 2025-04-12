
#ifndef TESTBUILD_VERTS_H
#define TESTBUILD_VERTS_H

#include "include/VBO.h"

namespace verts {
    extern  std::vector<Vertex> cube;

    extern std::vector<Vertex> sphere(float radius, unsigned int stacks, unsigned int slices);
}

#endif
