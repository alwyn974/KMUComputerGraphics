#include "object/Sphere.hpp"

#include "glm/gtc/constants.hpp"
#include "glm/vec3.hpp"
#include "glm/mat3x3.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

Sphere::Sphere(float rad, GLuint slices, GLuint stacks) : radius(rad), slices(slices), stacks(stacks)
{
    nVerts = (slices + 1) * (stacks + 1);
    elements = (slices * 2 * (stacks - 1)) * 3;

    // Verts
    float *v = new float[3 * nVerts];
    // Normals
    float *n = new float[3 * nVerts];
    // Tex coords
    float *tex = new float[2 * nVerts];
    // Index
    unsigned int *el = new unsigned int[elements];  //index

    // Generate the vertex data
    generateVerts(v, n, tex, el);
    //create vao, vbo and ibo here... (We didn't use std::vector here...)
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glGenBuffers(1, &vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVerts, v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vboNormal);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * nVerts, n, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    GLuint vboTexCoords;
    glGenBuffers(1, &vboTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nVerts, tex, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &iboElements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboElements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements, el, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete[] v;
    delete[] n;
    delete[] el;
    delete[] tex;
}

void Sphere::draw()
{
    glBindVertexArray(vaoHandle);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Sphere::generateVerts(float *verts, float *norms, float *tex, GLuint *el)
{
    // Generate positions and normals
    GLfloat theta, phi;
    GLfloat thetaFac = glm::two_pi<float>() / slices;
    GLfloat phiFac = glm::pi<float>() / stacks;
    GLfloat nx, ny, nz, s, t;
    GLuint idx = 0, tIdx = 0;
    for (GLuint i = 0; i <= slices; i++) {
        theta = i * thetaFac;
        s = (GLfloat) i / slices;
        for (GLuint j = 0; j <= stacks; j++) {
            phi = j * phiFac;
            t = (GLfloat) j / stacks;
            nx = sinf(phi) * cosf(theta);
            ny = sinf(phi) * sinf(theta);
            nz = cosf(phi);
            verts[idx] = radius * nx;
            verts[idx + 1] = radius * ny;
            verts[idx + 2] = radius * nz;
            norms[idx] = nx;
            norms[idx + 1] = ny;
            norms[idx + 2] = nz;
            idx += 3;

            tex[tIdx] = s;
            tex[tIdx + 1] = t;
            tIdx += 2;
        }
    }

    // Generate the element list
    idx = 0;
    for (GLuint i = 0; i < slices; i++) {
        GLuint stackStart = i * (stacks + 1);
        GLuint nextStackStart = (i + 1) * (stacks + 1);
        for (GLuint j = 0; j < stacks; j++) {
            if (j == 0) {
                el[idx] = stackStart;
                el[idx + 1] = stackStart + 1;
                el[idx + 2] = nextStackStart + 1;
                idx += 3;
            } else if (j == stacks - 1) {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j;
                idx += 3;
            } else {
                el[idx] = stackStart + j;
                el[idx + 1] = stackStart + j + 1;
                el[idx + 2] = nextStackStart + j + 1;
                el[idx + 3] = nextStackStart + j;
                el[idx + 4] = stackStart + j;
                el[idx + 5] = nextStackStart + j + 1;
                idx += 6;
            }
        }
    }
}

