#ifndef ___SPHERE_H
#define ___SPHERE_H

#include <GL/gl3w.h>
#include "glm/mat4x4.hpp"

#include <vector>

#include "Loader.hpp"

class Sphere {
public:
    explicit Sphere(float rad, GLuint slices, GLuint stacks);

    ~Sphere();
    void draw();

    int getVertexArrayHandle() const
    {
        return this->vaoHandle;
    }

    GLuint vaoHandle, vboPosition, vboNormal, iboElements;

private:
    GLuint nVerts, elements;
    float radius;
    GLuint slices, stacks;

    void generateVerts(float *verts, float *norms, float *tex, GLuint *el);
};

#endif
