#include "VBOTorus.hpp"

#include "GL/gl3w.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <cstdio>
#include <cmath>

VBOTorus::VBOTorus(float outerRadius, float innerRadius, int nsides, int nrings) :
    rings(nrings), sides(nsides)
{
    faces = sides * rings;
    int nVerts = sides * (rings + 1);   // One extra ring to duplicate first ring

    // Verts
    GLfloat * v = new GLfloat[3 * nVerts];
    // Normals
    GLfloat * n = new GLfloat[3 * nVerts];
    //     // Tex coords
    //     float * tex = new float[2 * nVerts];
    // Elements
    unsigned int *el = new unsigned int[6 * faces];

    // Generate the vertex data
    generateVerts(v, n, el, outerRadius, innerRadius);



    //create vao, vbo, ibo here



    delete[] v;
    delete[] n;
    delete[] el;

    glBindVertexArray(0);
}

VBOTorus::~VBOTorus()
{
    delete shaderProgram;
}

void VBOTorus::draw() const
{
}

void VBOTorus::generateVerts(GLfloat *verts, GLfloat *norms, unsigned int *el, float outerRadius, float innerRadius)
{
    float TWOPI = 2 * glm::pi<float>();

    float ringFactor = (float) (TWOPI / rings);
    float sideFactor = (float) (TWOPI / sides);
    int idx = 0, tidx = 0;
    for (int ring = 0; ring <= rings; ring++) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for (int side = 0; side < sides; side++) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = (outerRadius + innerRadius * cv);
            verts[idx] = r * cu;
            verts[idx + 1] = r * su;
            verts[idx + 2] = innerRadius * sv;

            norms[idx] = cv * cu * r;
            norms[idx + 1] = cv * su * r;
            norms[idx + 2] = sv * r;

            //             tex[tidx] = (float)(u / TWOPI);
            //             tex[tidx+1] = (float)(v / TWOPI);
            //            tidx += 2;
            // Normalize
            float len = sqrt(norms[idx] * norms[idx] +
                             norms[idx + 1] * norms[idx + 1] +
                             norms[idx + 2] * norms[idx + 2]);
            norms[idx] /= len;
            norms[idx + 1] /= len;
            norms[idx + 2] /= len;
            idx += 3;
        }
    }

    idx = 0;
    for (int ring = 0; ring < rings; ring++) {
        int ringStart = ring * sides;
        int nextRingStart = (ring + 1) * sides;
        for (int side = 0; side < sides; side++) {
            int nextSide = (side + 1) % sides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx + 1] = (nextRingStart + side);
            el[idx + 2] = (nextRingStart + nextSide);
            el[idx + 3] = ringStart + side;
            el[idx + 4] = nextRingStart + nextSide;
            el[idx + 5] = (ringStart + nextSide);
            idx += 6;
        }
    }
}


