//
// Created by alwyn on 23/11/2023.
//

#include "object/Bunny.hpp"
#include "object/data/BunnyData.hpp"

Bunny::Bunny() : vaoHandle(0)
{
    initialize();
}

void Bunny::draw(const MaterialColor &materialColor) const
{
    glBindVertexArray(vaoHandle);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(glm::uint32), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Bunny::initialize()
{
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelVertices), &modelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        sizeof(float) * 8, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    GLuint vboNormals;
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelVertices), &modelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        1, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        sizeof(float) * 8, // stride
        (void *) (sizeof(float) * 3) // array buffer offset
    );
    glEnableVertexAttribArray(1);

    GLuint vboIndices;
    glGenBuffers(1, &vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelIndices), &modelIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}
