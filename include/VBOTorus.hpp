#ifndef VBOTORUS_H
#define VBOTORUS_H

#include "GL/gl3w.h"
#include "gl/GL.h"
#include "glm/mat4x4.hpp"

class VBOTorus {
public:
    explicit VBOTorus(float outerRadius, float innerRadius, int nsides, int nrings);

    virtual ~VBOTorus();

    void draw() const;
private:
    unsigned int vaoHandle;
    int faces, rings, sides;

    GLuint vbo_cube_vertices, vbo_cube_normals, ibo_cube_elements;

    void generateVerts(GLfloat *verts, GLfloat *norms, unsigned int *el, float outerRadius, float innerRadius);
};

#endif // VBOTORUS_H
