#ifndef VBOTORUS_H
#define VBOTORUS_H

#include "gl/GL.h"
#include "glm/mat4x4.hpp"

class VBOTorus {
public:
    VBOTorus(float, float, int, int);

    virtual ~VBOTorus();

    void draw() const;
private:
    unsigned int vaoHandle;
    int faces, rings, sides;

    GLuint vbo_cube_vertices, vbo_cube_normals, ibo_cube_elements;

    void generateVerts(float *, float *, unsigned int *, float, float);
};

#endif // VBOTORUS_H
