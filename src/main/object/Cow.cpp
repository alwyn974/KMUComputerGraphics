//
// Created by alwyn on 23/11/2023.
//

#include "object/Cow.hpp"
#include "object/data/CowData.hpp"

Cow::Cow() :vaoHandle(0)
{
    initialize();
}

void Cow::draw() const
{
    glBindVertexArray(vaoHandle);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size / sizeof(glm::uint32), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Cow::initialize()
{
    std::vector<glm::vec3> normals(1732); //# of vertices 1732 -> # of normal 1732
    std::vector<int> meanNormals(1732); // counter for mean normal
    for (int i = 0; i < 1732; i++) {
        const glm::vec3 &v0 = vertices[nvertices[i * 3]]; // 1st vertex
        const glm::vec3 &v1 = vertices[nvertices[i * 3 + 1]]; // 2nd vertex
        const glm::vec3 &v2 = vertices[nvertices[i * 3 + 2]]; // 3rd vertex
        glm::vec3 n = glm::cross((v1 - v0), (v2 - v0)); // Cross product
        n = glm::normalize(n);
        normals[nvertices[i * 3]] += n; // Set the same normal to each vertex
        meanNormals[nvertices[i * 3]]++;
        normals[nvertices[i * 3 + 1]] += n;
        meanNormals[nvertices[i * 3 + 1]]++;
        normals[nvertices[i * 3 + 2]] += n;
        meanNormals[nvertices[i * 3 + 2]]++;
    }
    for (const auto &item: meanNormals)
        normals[item] /= item;

    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    GLuint vboVertices;
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    GLuint vboNormals;
    glGenBuffers(1, &vboNormals);
    glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(
        1, // attribute
        3, // number of elements per vertex, here (x,y,z)
        GL_FLOAT, // type of each element
        GL_FALSE, // take our values as-is
        0, // stride
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(1);

    GLuint iboElements;
    glGenBuffers(1, &iboElements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboElements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nvertices), &nvertices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}
